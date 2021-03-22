import java.util.Random;
import java.util.ArrayList;
import java.util.Arrays;
import java.rmi.Naming;
import java.rmi.RemoteException;

public class Main {
	// How many nodes and how many edges to create.
	private static final int GRAPH_NODES = 1000;
	private static final int GRAPH_EDGES = 2000;

	// How many searches to perform
	private static final int SEARCHES = 50;

	// Upper limit for the transitive search
	private static final int TRANSITIVE_MAX = 10;

	private static Node[] nodes;
	private static Node[] remoteNodes;

	private static Random random = new Random(0);
	private static Searcher remoteSearcher;
	private static NodeFactory remoteNodeFactory;
	private static Searcher searcher = new SearcherImpl();

	/**
	 * Creates nodes of a graph.
	 * 
	 * @param howMany number of nodes
	 */
	public static void createNodes(int howMany) {
		try {
			nodes = new Node[howMany];
			remoteNodes = new Node[howMany];

			for (int i = 0; i < howMany; i++) {
				nodes[i] = new NodeImpl();
				remoteNodes[i] = remoteNodeFactory.createNode();
			}
		} catch (Exception e) {
            System.err.println("Main exception: " + e.toString());
            e.printStackTrace();
		}
	}

	/**
	 * Creates a fully connected graph.
	 */
	public static void connectAllNodes() {
		try {
			for (int idxFrom = 0; idxFrom < nodes.length; idxFrom++) {
				for (int idxTo = idxFrom + 1; idxTo < nodes.length; idxTo++) {
					nodes[idxFrom].addNeighbor(nodes[idxTo]);
					nodes[idxTo].addNeighbor(nodes[idxFrom]);
				}
			}
		} catch (Exception e) {
            System.err.println("Main exception: " + e.toString());
            e.printStackTrace();
		}
	}

	/**
	 * Creates a randomly connected graph.
	 * 
	 * @param howMany number of edges
	 */
	public static void connectSomeNodes(int howMany) {
		try {
			for (int i = 0; i < howMany; i++) {
				final int idxFrom = random.nextInt(nodes.length);
				final int idxTo = random.nextInt(nodes.length);

				nodes[idxFrom].addNeighbor(nodes[idxTo]);
				remoteNodes[idxFrom].addNeighbor(remoteNodes[idxTo]);
			}
		} catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
		}
	}

	/**
	 * Runs a quick measurement on the graph.
	 * 
	 * @param howMany number of measurements
	 */
	public static void searchBenchmark(int howMany) {
		try {

			// Display measurement header.
			ArrayList<String> headers = new ArrayList<String>(Arrays.asList("Attempt", "Distance", "Time", "RemoteSearcher", "RemoteNodes", "RemoteSearcherNodes"));
			for (int i = 1; i < TRANSITIVE_MAX; i++) {
				headers.add("Transitive" + i);
			}
			System.out.println(String.join(" ", headers));

			for (int i = 0; i < howMany; i++) {
				ArrayList<Long> results = new ArrayList<Long>();
				results.add((long)i);

				// Select two random nodes.
				final int idxFrom = random.nextInt(nodes.length);
				final int idxTo = random.nextInt(nodes.length);

				// Standard
				final long startTimeNs = System.nanoTime();
				final int distance = searcher.getDistance(nodes[idxFrom], nodes[idxTo]);
				results.add((long)distance);
				results.add((System.nanoTime() - startTimeNs) / 1000);

				// Remote searcher
				final long startTimeRemoteSearcherNs = System.nanoTime();
				final int distanceRemoteSearcher = remoteSearcher.getDistance(nodes[idxFrom], nodes[idxTo]);
				results.add((System.nanoTime() - startTimeRemoteSearcherNs) / 1000);

				// Remote nodes
				final long startTimeRemoteNodesNs = System.nanoTime();
				final int distanceRemoteNodes = searcher.getDistance(remoteNodes[idxFrom], remoteNodes[idxTo]);
				results.add((System.nanoTime() - startTimeRemoteNodesNs) / 1000);

				// Remote searcher + remote nodes
				final long startTimeRemoteSearcherNodesNs = System.nanoTime();
				final int distanceRemoteSearcherNodes = remoteSearcher.getDistance(remoteNodes[idxFrom], remoteNodes[idxTo]);
				results.add((System.nanoTime() - startTimeRemoteSearcherNodesNs) / 1000);
				
				// Measure transitive search
				for (int n = 1; n < TRANSITIVE_MAX; n++) {
					long transitiveNodesNs = System.nanoTime();
					int transitiveDistance = remoteSearcher.getDistanceTransitive(n, remoteNodes[idxFrom], remoteNodes[idxTo]);
					results.add((System.nanoTime() - transitiveNodesNs) / 1000);
				}

				// Print the measurement result.
				System.out.println(results.toString().replace("[", "").replace("]", "").replace(",", ""));
			}
			
		} catch (Exception e) {
            System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		if (args.length != 2) {
			System.err.println("Usage: javac Main <NUMBER_OF_EDGES> <ADDRESS_OF_REMOTE_SERVER>");
			return;
		}
		try {
			String address = args[1];
			remoteSearcher = (Searcher) Naming.lookup(String.format("//%s/RemoteSearcher", address));
			remoteNodeFactory = (NodeFactory) Naming.lookup(String.format("//%s/RemoteNodeFactory", address));	
		} catch (Exception e) {
            System.err.println("Remote exception: " + e.toString());
			e.printStackTrace();
			return;
		}
		// Create a randomly connected graph and do a quick measurement.
		// Consider replacing connectSomeNodes with connectAllNodes to verify that all distances are equal to one.
		createNodes(GRAPH_NODES);
		connectSomeNodes(Integer.parseInt(args[0]));
		searchBenchmark(SEARCHES);
	}
}
