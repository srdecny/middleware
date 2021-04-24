import java.io.IOException;
import java.io.InputStreamReader;
import java.io.LineNumberReader;
import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.stream.*;
import java.util.function.Function;

import javax.jms.*;

import org.apache.activemq.artemis.jms.client.ActiveMQConnectionFactory;

public class Client {
	
	/****	CONSTANTS	****/
	
	// name of the property specifying client's name
	public static final String CLIENT_NAME_PROPERTY = "clientName";

	// name of the topic for publishing offers
	public static final String OFFER_TOPIC = "Offers";

	public static final String BALANCE_PROPERTY = "balance";

	public static final String ACCOUNT_NUMBER_PROPERTY = "accountNumber";

	public static final String OFFER_TYPE_KEY = "OfferType";
	public static final String OFFER_MESSAGE = "OfferReply";
	public static final String OFFER_REQUEST = "OfferRequest";
	
	/****	PRIVATE VARIABLES	****/
	
	// client's unique name
	private String clientName;

	// client's account number
	private int accountNumber;
	
	// offered goods, mapped by name
	private Map<String, Goods> offeredGoods = new HashMap<String, Goods>();
	
	// available goods, mapped by seller's name 
	private Map<String, List<Goods>> availableGoods = new HashMap<String, List<Goods>>();
	
	// reserved goods, mapped by name of the goods
	private Map<String, Goods> reservedGoods = new HashMap<String, Goods>();
	
	// buyer's names, mapped by their account numbers
	private Map<Integer, String> reserverAccounts = new HashMap<Integer, String>();
	
	// buyer's reply destinations, mapped by their names
	private Map<String, Destination> reserverDestinations= new HashMap<String, Destination>();
	
	// connection to the broker
	private Connection conn;
	
	// session for user-initiated synchronous messages
	private Session clientSession;

	// session for listening and reacting to asynchronous messages
	private Session eventSession;
	
	// sender for the clientSession
	private MessageProducer clientSender;
	
	// sender for the eventSession
	private MessageProducer eventSender;

	// receiver of synchronous replies
	private MessageConsumer replyReceiver;
	
	// topic to send and receiver offers
	private Topic offerTopic;
	
	// queue for sending messages to bank
	private Queue toBankQueue;
	
	// queue for receiving synchronous replies
	private Queue replyQueue;


	
	// reader of lines from stdin
	private LineNumberReader in = new LineNumberReader(new InputStreamReader(System.in));
	
	/****	PRIVATE METHODS	****/
	
	/*
	 * Constructor, stores clientName, connection and initializes maps
	 */
	private Client(String clientName, Connection conn) {
		this.clientName = clientName;
		this.conn = conn;
		
		// generate some goods
		generateGoods();
	}
	
	/*
	 * Generate goods items
	 */
	private void generateGoods() {
		Random rnd = new Random();
		for (int i = 0; i < 10; ++i) {
			String name = "";
			
			for (int j = 0; j < 4; ++j) {
				char c = (char) ('A' + rnd.nextInt('Z' - 'A'));
				name += c;
			}
			
			offeredGoods.put(name, new Goods(name, rnd.nextInt(10000)));
		}
	}
	
	/*
	 * Set up all JMS entities, get bank account, publish first goods offer 
	 */
	private void connect() throws JMSException {
		// create two sessions - one for synchronous and one for asynchronous processing
		clientSession = conn.createSession(false, Session.AUTO_ACKNOWLEDGE);
		eventSession = conn.createSession(false, Session.AUTO_ACKNOWLEDGE);
		
		// create (unbound) senders for the sessions
		clientSender = clientSession.createProducer(null);
		eventSender = eventSession.createProducer(null);
		
		// create queue for sending messages to bank
		toBankQueue = clientSession.createQueue(Bank.BANK_QUEUE);
		// create a temporary queue for receiving messages from bank
		Queue fromBankQueue = eventSession.createTemporaryQueue();

		// temporary receiver for the first reply from bank
		// note that although the receiver is created within a different session
		// than the queue, it is OK since the queue is used only within the
		// client session for the moment
		MessageConsumer tmpBankReceiver = clientSession.createConsumer(fromBankQueue);        
		
		// start processing messages
		conn.start();
		
		// request a bank account number
		Message msg = eventSession.createTextMessage(Bank.NEW_ACCOUNT_MSG);
		msg.setStringProperty(CLIENT_NAME_PROPERTY, clientName);
		// set ReplyTo that Bank will use to send me reply and later transfer reports
		msg.setJMSReplyTo(fromBankQueue);
		clientSender.send(toBankQueue, msg);
		
		// get reply from bank and store the account number
		TextMessage reply = (TextMessage) tmpBankReceiver.receive();
		accountNumber = Integer.parseInt(reply.getText());
		System.out.println("Account number: " + accountNumber);
		
		// close the temporary receiver
		tmpBankReceiver.close();
		
		// temporarily stop processing messages to finish initialization
		conn.stop();
		
		/* Processing bank reports */
		
		// create consumer of bank reports (from the fromBankQueue) on the event session
		MessageConsumer bankReceiver = eventSession.createConsumer(fromBankQueue);
		
		// set asynchronous listener for reports, using anonymous MessageListener
		// which just calls our designated method in its onMessage method
		bankReceiver.setMessageListener(new MessageListener() {
			@Override
			public void onMessage(Message msg) {
				try {
					processBankReport(msg);
				} catch (JMSException e) {
					e.printStackTrace();
				}
			}
		});

		// TODO finish the initialization
		
		/* Step 1: Processing offers */
		
		// create a topic both for publishing and receiving offers
		// hint: Sessions have a createTopic() method
		
		offerTopic = eventSession.createTopic(OFFER_TOPIC);

		// create a consumer of offers from the topic using the event session
		replyReceiver = eventSession.createConsumer(offerTopic);
		
		// set asynchronous listener for offers (see above how it can be done)
		// which should call processOffer()
		replyReceiver.setMessageListener(new MessageListener() {
			@Override
			public void onMessage(Message msg) {
				try {
					if (!msg.getStringProperty(CLIENT_NAME_PROPERTY).equals(clientName)) {
						if (msg.getStringProperty(OFFER_TYPE_KEY).equals(OFFER_REQUEST)) {
							publishGoodsList(eventSender, eventSession);
						} else {
							processOffer(msg);
						}
					}
				} catch (JMSException e) {
					e.printStackTrace();
				}
			}
		});
		

		/* Step 2: Processing sale requests */
		
		// create a queue for receiving sale requests (hint: Session has createQueue() method)
		// note that Session's createTemporaryQueue() is not usable here, the queue must have a name
		// that others will be able to determine from clientName (such as clientName + "SaleQueue")
		Queue saleRequests = eventSession.createQueue(clientName + "SaleQueue");
		// create consumer of sale requests on the event session
		MessageConsumer saleReceiver = eventSession.createConsumer(saleRequests);

		// set asynchronous listener for sale requests (see above how it can be done)
		// which should call processSale()
		saleReceiver.setMessageListener(new MessageListener() {
			@Override
			public void onMessage(Message msg) {
				try {
					processSale(msg);
				} catch (JMSException e) {
					e.printStackTrace();
				}
			}
		});
		// end TODO
		
		// create temporary queue for synchronous replies
		replyQueue = clientSession.createTemporaryQueue();
		
		// create synchronous receiver of the replies
		replyReceiver = clientSession.createConsumer(replyQueue);
		
		// restart message processing
		conn.start();

		// send list of offered goods
		publishGoodsList(clientSender, clientSession);

		// Ask others to send their offered goods
		Message offerRequest = clientSession.createObjectMessage();
		offerRequest.setStringProperty(OFFER_TYPE_KEY, OFFER_REQUEST);
		offerRequest.setStringProperty(CLIENT_NAME_PROPERTY, clientName);
		clientSender.send(offerTopic, offerRequest);

	}

	/*
	 * Publish a list of offered goods
	 * Parameter is an (unbound) sender that fits into current session
	 * Sometimes we publish the list on user's request, sometimes we react to an event
	 */
	private void publishGoodsList(MessageProducer sender, Session session) throws JMSException {
		// TODO
		
		// create a message (of appropriate type) holding the list of offered goods
		// which can be created like this: new ArrayList<Goods>(offeredGoods.values())
		
		// don't forget to include the clientName in the message so other clients know
		// who is sending the offer - see how connect() does it when sending message to bank
		
		// send the message using the sender passed as parameter 

		ObjectMessage msg = session.createObjectMessage();
		msg.setStringProperty(CLIENT_NAME_PROPERTY, clientName);
		msg.setStringProperty(OFFER_TYPE_KEY, OFFER_MESSAGE);
		synchronized(offeredGoods) {
			msg.setObject(new ArrayList<Goods>(offeredGoods.values()));
		}
		sender.send(offerTopic, msg);
	}
	
	/*
	 * Send empty offer and disconnect from the broker 
	 */
	private void disconnect() throws JMSException {
		// delete all offered goods
		offeredGoods.clear();
		
		// send the empty list to indicate client quit
		publishGoodsList(clientSender, clientSession);
		
		// close the connection to broker
		conn.close();
	}
	
	/*
	 * Print known goods that are offered by other clients
	 */
	private void list() {
		System.out.println("Available goods (name: price):");
		// iterate over sellers
		synchronized(availableGoods) {
			for (String sellerName : availableGoods.keySet()) {
				System.out.println("From " + sellerName);
				// iterate over goods offered by a seller
				for (Goods g : availableGoods.get(sellerName)) {
					System.out.println("  " + g);
				}
			}
		}
	}

	private void printBalance() throws JMSException {
		Queue fromBankQueue = clientSession.createTemporaryQueue();
		MessageConsumer tmpBankReceiver = clientSession.createConsumer(fromBankQueue);

		TextMessage balanceQuery = clientSession.createTextMessage();
		balanceQuery.setText(Bank.BALANCE_CHECK_MSG);
		balanceQuery.setIntProperty(Client.ACCOUNT_NUMBER_PROPERTY, accountNumber);
		balanceQuery.setJMSReplyTo(fromBankQueue);
		clientSender.send(toBankQueue, balanceQuery);

		TextMessage balanceReply = (TextMessage) tmpBankReceiver.receive();
		Integer balance = balanceReply.getIntProperty(Client.BALANCE_PROPERTY);
		System.out.println("Balance: " + balance.toString());
	}

	/*
	 * Main interactive user loop
	 */
	private void loop() throws IOException, JMSException {
		// first connect to broker and setup everything
		connect();
		
		loop:
		while (true) {
			System.out.println("\nAvailable commands (type and press enter):");
			System.out.println(" l - list available goods");
			System.out.println(" p - publish list of offered goods");
			System.out.println(" b - buy goods");
			System.out.println(" a - print account balance");
			System.out.println(" q - quit");
			// read first character
			int c = in.read();
			// throw away rest of the buffered line
			while (in.ready()) in.read();
			switch (c) {
				case 'q':
					disconnect();
					break loop;
				case 'b':
					buy();
					break;
				case 'a':
					printBalance();
					break;
				case 'l':
					list();
					break;
				case 'p':
					publishGoodsList(clientSender, clientSession);
					System.out.println("List of offers published");
					break;
				case '\n':
				default:
					break;
			}
		}
	}
	
	/*
	 * Perform buying of goods
	 */
	private void buy() throws IOException, JMSException {
		// get information from the user
		System.out.println("Enter seller name:");
		String sellerName = in.readLine();
		System.out.println("Enter goods name:");
		String goodsName = in.readLine();

		// check if the seller exists
		List<Goods> sellerGoods = availableGoods.get(sellerName);
		if (sellerGoods == null) {
			System.out.println("Seller does not exist: " + sellerName);
			return;
		}
		List<String> goodsNames = sellerGoods.stream().map(g -> g.name).collect(Collectors.toList());
		if (!goodsNames.contains(goodsName)) {
			System.out.println("Seller does not offer such goods.");
			return;
		}
		
		// TODO
		
		// First consider what message types clients will use for communicating a sale
		// we will need to transfer multiple values (of String and int) in each message 
		// MapMessage? ObjectMessage? TextMessage with extra properties?
		
		/* Step 1: send a message to the seller requesting the goods */
		
		// create local reference to the seller's queue
		// similar to Step 2 in connect() but using sellerName instead of clientName
		Queue sellerQueue = clientSession.createQueue(sellerName + "SaleQueue");
		// create message requesting sale of the goods
		// includes: clientName, goodsName, accountNumber
		// also include reply destination that the other client will use to send reply (replyQueue)
		// how? see how connect() uses SetJMSReplyTo() 
		SaleRequest saleRequest = new SaleRequest(clientName, goodsName, accountNumber);
		ObjectMessage message = clientSession.createObjectMessage();
		message.setObject(saleRequest);
		message.setJMSReplyTo(replyQueue);
					
		// send the message (with clientSender)
		clientSender.send(sellerQueue, message);
		/* Step 2: get seller's response and process it */
		
		// receive the reply (synchronously, using replyReceiver)
		ObjectMessage requestReply = (ObjectMessage)replyReceiver.receive();
		SaleReply saleReply = (SaleReply)requestReply.getObject();	
		// parse the reply (depends on your selected message format)
		// distinguish between "sell denied" and "sell accepted" message
		// in case of "denied", report to user and return from this method
		// in case of "accepted"
		if (!saleReply.accepted) {
			System.out.println("Seller denied the sell request.");
			return;
		}
		// - obtain seller's account number and price to pay
		int price = saleReply.price;
		int sellerAccount = saleReply.accountNumber;

		/* Step 3: send message to bank requesting money transfer */
		
		// create message ordering the bank to send money to seller
		MapMessage bankMsg = clientSession.createMapMessage();
		bankMsg.setStringProperty(CLIENT_NAME_PROPERTY, clientName);
		bankMsg.setInt(Bank.ORDER_TYPE_KEY, Bank.ORDER_TYPE_SEND);
		bankMsg.setInt(Bank.ORDER_RECEIVER_ACC_KEY, sellerAccount);
		bankMsg.setInt(Bank.AMOUNT_KEY, price);
		
		System.out.println("Sending $" + price + " to account " + sellerAccount);
		
		// send message to bank
		clientSender.send(toBankQueue, bankMsg);

		/* Step 4: wait for seller's sale confirmation */
		
		// receive the confirmation, similar to Step 2
		ObjectMessage confirmationMessage = (ObjectMessage)replyReceiver.receive();
		SaleConfirmation confirmation = (SaleConfirmation)confirmationMessage.getObject();

		// parse message and verify it's confirmation message
		// report successful sale to the user
		if (!confirmation.confirmed) {
			System.out.println("Sale not confirmed by seller!");
		} else {
			System.out.println("Confirmed sale of goods " + confirmation.goodsName);
		}
	}
	
	/*
	 * Process a message with goods offer
	 */
	private void processOffer(Message msg) throws JMSException {
		// TODO
		synchronized(this) {
			// parse the message, obtaining sender's name and list of offered goods
			ObjectMessage offer = (ObjectMessage) msg;
			String senderName = offer.getStringProperty(CLIENT_NAME_PROPERTY);
			ArrayList<Goods> offeredGoods = (ArrayList<Goods>) offer.getObject();
			// should ignore messages sent from myself
			if (senderName.equals(clientName)) return;
			// store the list into availableGoods (replacing any previous offer)
			// empty list means disconnecting client, remove it from availableGoods completely
			if (offeredGoods.isEmpty()) {
				availableGoods.remove(senderName);
			} else {
				availableGoods.put(senderName, offeredGoods);
			}
		}	
	}
	
	/*
	 * Process message requesting a sale
	 */
	private void processSale(Message msg) throws JMSException {
		// TODO
		
		/* Step 1: parse the message */
		// distinguish that it's the sale request message
		if (!(msg instanceof ObjectMessage)) return;
		ObjectMessage requestMessage = (ObjectMessage) msg;
		SaleRequest request = (SaleRequest) requestMessage.getObject();
		Destination replyDestination = msg.getJMSReplyTo();
		// obtain buyer's name (buyerName), goods name (goodsName) , buyer's account number (buyerAccount)
		
		// also obtain reply destination (buyerDest)
		// how? see for example Bank.processTextMessage()

		/* Step 2: decide what to do and modify data structures accordingly */
			synchronized(this) {	
			// check if we still offer this goods
			Goods goods = offeredGoods.get(request.goodsName);
			if (goods == null) {
				SaleReply reply = new SaleReply(false, -1, -1);
				ObjectMessage replyMessage = eventSession.createObjectMessage();
				replyMessage.setObject(reply);
				eventSender.send(replyDestination, replyMessage);
			}

			// if yes, we should remove it from offeredGoods and publish new list
			// also it's useful to create a list of "reserved goods" together with buyer's information
			// such as name, account number, reply destination
			offeredGoods.remove(request.goodsName);
			reservedGoods.put(request.buyerName, goods);
			reserverAccounts.put(request.accountNumber, request.buyerName);
			reserverDestinations.put(request.buyerName, replyDestination);
			
			/* Step 3: send reply message */
			
			// prepare reply message (accept or deny)
			// accept message includes: my account number (accountNumber), price (goods.price)
			SaleReply reply = new SaleReply(true, accountNumber, goods.price);
			ObjectMessage replyMessage = eventSession.createObjectMessage();
			replyMessage.setObject(reply);	
			// send reply
			eventSender.send(replyDestination, replyMessage);
		}
	}
	
	/*
	 * Process message with (transfer) report from the bank
	 */
	private void processBankReport(Message msg) throws JMSException {
		synchronized(this) {	
			/* Step 1: parse the message */
			// Bank reports are sent as MapMessage
			if (msg instanceof MapMessage) {
				MapMessage mapMsg = (MapMessage) msg;
				// get report number
				int cmd = mapMsg.getInt(Bank.REPORT_TYPE_KEY);
				int buyerAccount = mapMsg.getInt(Bank.REPORT_SENDER_ACC_KEY);
				// match the sender account with sender
				String buyerName = reserverAccounts.get(buyerAccount);
				// get the buyer's destination
				Destination buyerDest = reserverDestinations.get(buyerName);
				// remove the reserved goods and buyer-related information (we don't need it any more)
				reserverDestinations.remove(buyerName);
				reserverAccounts.remove(buyerAccount);
				// match the reserved goods
				Goods g = reservedGoods.get(buyerName);

				// No payment because buyer did not send enough cash
				if ( cmd == Bank.REPORT_TYPE_SMALL_BALANCE) {
					// Restore the goods
					offeredGoods.put(g.name, g);
					reservedGoods.remove(buyerName);

					// Tell the buyer the order is cancelled
					SaleConfirmation confirmation = new SaleConfirmation(false, g.name);
					ObjectMessage confirmationMessage = eventSession.createObjectMessage();
					confirmationMessage.setObject(confirmation);
					eventSender.send(buyerDest, confirmationMessage);	
				} else if (cmd == Bank.REPORT_TYPE_RECEIVED) {
					
					int amount = mapMsg.getInt(Bank.AMOUNT_KEY);
					System.out.println("Received $" + amount + " from " + buyerName);

					/* Step 2: decide what to do and modify data structures accordingly */
					// did he pay enough?
					if (amount >= g.price) {

						reservedGoods.remove(buyerName);

						// prepare sale confirmation message
						// includes: goods name (g.name)
						SaleConfirmation confirmation = new SaleConfirmation(true, g.name);
						ObjectMessage confirmationMessage = eventSession.createObjectMessage();
						confirmationMessage.setObject(confirmation);
						// send reply (destination is buyerDest)
						eventSender.send(buyerDest, confirmationMessage);	

					// Buyer didn't send enough cash
					} else {
						// Restore the goods
						offeredGoods.put(g.name, g);
						reservedGoods.remove(buyerName);

						// Return the cash

						MapMessage bankMsg = eventSession.createMapMessage();
						bankMsg.setStringProperty(CLIENT_NAME_PROPERTY, clientName);
						bankMsg.setInt(Bank.ORDER_TYPE_KEY, Bank.ORDER_TYPE_SEND);
						bankMsg.setInt(Bank.ORDER_RECEIVER_ACC_KEY, buyerAccount);
						bankMsg.setInt(Bank.AMOUNT_KEY, amount);
						eventSender.send(toBankQueue, bankMsg);

						// Tell the buyer the order is cancelled
						SaleConfirmation confirmation = new SaleConfirmation(false, g.name);
						ObjectMessage confirmationMessage = eventSession.createObjectMessage();
						confirmationMessage.setObject(confirmation);
						eventSender.send(buyerDest, confirmationMessage);	
					}
				} else {
					System.out.println("Received unknown MapMessage:\n: " + msg);
				}
			} else {
				System.out.println("Received unknown message:\n: " + msg);
			}
		}
	}
	
	/**** PUBLIC METHODS ****/
	
	/*
	 * Main method, creates client instance and runs its loop
	 */
	public static void main(String[] args) {

		if (args.length != 1) {
			System.out.println(args);
			System.err.println("Usage: ./client <clientName>");
			return;
		}
		
		// create connection to the broker.
		try (ActiveMQConnectionFactory connectionFactory = new ActiveMQConnectionFactory("tcp://localhost:61616");
				Connection connection = connectionFactory.createConnection()) {
			// create instance of the client
			Client client = new Client(args[0], connection);
			
			// perform client loop
			client.loop();
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}
}
