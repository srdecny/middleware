
import com.hazelcast.client.HazelcastClient;
import com.hazelcast.client.config.ClientConfig;
import com.hazelcast.config.Config;
import com.hazelcast.core.Hazelcast;
import com.hazelcast.core.HazelcastInstance;
import com.hazelcast.map.*;
import com.hazelcast.core.*;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.LineNumberReader;
import java.nio.channels.SelectableChannel;
import java.io.*;
import java.util.*;
import java.util.concurrent.*;


public class Client implements Serializable {

	// Reader for user input
	private LineNumberReader in = new LineNumberReader(new InputStreamReader(System.in));
	// Connection to the cluster
	private HazelcastInstance hazelcast;
	// The name of the user
	private String userName;
	// Do not keep any other state here - all data should be in the cluster

	/**
	 * Create a client for the specified user.
	 * @param userName user name used to identify the user
	 */
	public Client(String userName) {
		this.userName = userName;
		// Connect to the Hazelcast cluster
		ClientConfig config = new ClientConfig();
		hazelcast = HazelcastClient.newHazelcastClient(config);
	}

	/**
	 * Disconnect from the Hazelcast cluster.
	 */
	public void disconnect() {
		// Disconnect from the Hazelcast cluster
		hazelcast.shutdown();
	}

	/**
	 * Show the currently selected document to the user
	 */
	private void showCommand() throws Exception {

		Optional<String> maybeSelectedDocument = getSelectedDocument();
		if (maybeSelectedDocument.isEmpty()) {
			System.out.println("No document selected!");
		} else {
			String documentName = maybeSelectedDocument.get();
			// Fetch the document from the cluster
			// If it does not exist, it will be created
			IExecutorService executorService = hazelcast.getExecutorService("executorService");
			// Set up a promise for the document 
			Future<Document> futureDocument = executorService.submit(new FetchDocumentTask(documentName));

			// Increment document's view count
			// This is done atomically via Entry Processor
			IMap<String, Integer> documentsViewCount = hazelcast.getMap(IMaps.DOCUMENTS_VIEW_COUNT);
			documentsViewCount.executeOnKey(documentName, new IncrementDocumentViewProcessor());

			// Show the document content
			Document document = futureDocument.get();
			System.out.println("The document is:");
			System.out.println(document.getContent());
		}
	}

	/**
	 * Show the next document in the list of favorites of the user.
	 * Select the next document, so that running this command repeatedly
	 * will cyclically show all favorite documents of the user.
	 */
	private void nextFavoriteCommand() throws Exception {
		IMap<String, Collection<String>> favoriteDocuments = hazelcast.getMap(IMaps.FAVORITE_DOCUMENTS);
		IMap<String, String> selectedDocuments = hazelcast.getMap(IMaps.SELECTED_DOCUMENTS);
		Collection<String> favoriteList = favoriteDocuments.get(userName);
		if (favoriteList == null || favoriteList.size() == 0) {
			System.out.println("No favorite documents!");
		} else {
			Optional<String> selectedDocument = getSelectedDocument();
			List<String> favorites = new ArrayList<String>(favoriteList);

			// Start from the beginning of the favorite list
			Integer documentIndex = (selectedDocument.isEmpty() || favorites.indexOf(selectedDocument.get()) == -1) ? 0 : favorites.indexOf(selectedDocument.get());
			selectedDocuments.set(userName, favorites.get((documentIndex + 1) % favorites.size()));
			showCommand();
		}
	}

	/**
	 * Add the current selected document name to the list of favorite documents of the user.
	 * If the list already contains the document name, do nothing.
	 */
	private void addFavoriteCommand() {
		Optional<String> maybeSelectedDocument = getSelectedDocument();
		if (maybeSelectedDocument.isEmpty()) {
			System.out.println("No document selected!");
		} else {
			String selectedDocument = maybeSelectedDocument.get();
			IMap<String, Collection<String>> favoriteDocuments = hazelcast.getMap(IMaps.FAVORITE_DOCUMENTS);
			favoriteDocuments.executeOnKey(userName, new AddValueToCollectionProcessor<String, String>(selectedDocument, new LinkedHashSet<String>()));
			System.out.printf("Added %s to favorites%n", selectedDocument);
		}
	}
	/**
	 * Remove the current selected document name from the list of favorite documents of the user.
	 * If the list does not contain the document name, do nothing.
	 */
	private void removeFavoriteCommand(){
		Optional<String> maybeSelectedDocument = getSelectedDocument();
		if (maybeSelectedDocument.isEmpty()) {
			System.out.println("No document selected!");
		} else {
			String selectedDocument = maybeSelectedDocument.get();
			IMap<String, Collection<String>> favoriteDocuments = hazelcast.getMap(IMaps.FAVORITE_DOCUMENTS);
			favoriteDocuments.executeOnKey(userName, new RemoveValueFromCollectionProcessor<String, String>(selectedDocument));
			System.out.printf("Removed %s from favorites%n", selectedDocument);
		}
	}
	/**
	 * Add the current selected document name to the list of favorite documents of the user.
	 * If the list already contains the document name, do nothing.
	 */
	private void listFavoritesCommand() {
		// for(String favoriteDocumentName: favoriteList)
		//	System.out.println(favoriteDocumentName);
		Optional<String> maybeSelectedDocument = getSelectedDocument();
		if (maybeSelectedDocument.isEmpty()) {
			System.out.println("No document selected!");
		} else {
			String selectedDocument = maybeSelectedDocument.get();
			IMap<String, Collection<String>> favoriteDocuments = hazelcast.getMap(IMaps.FAVORITE_DOCUMENTS);
			Collection<String> favoriteList = favoriteDocuments.get(userName);
			if (favoriteList == null) {
				System.out.println("No favorite documents!");
			} else {
				System.out.println("Your list of favorite documents:");
				for (String favoriteDocument : favoriteList) {
					System.out.println(favoriteDocument);
				}
			}
		}
	}

	/**
	 * Show the view count and comments of the current selected document.
	 */
	private void infoCommand() throws Exception {
		System.out.println("Enter document name:");
		String documentName = in.readLine();

		System.out.printf("Info about %s:%n", documentName);

		IMap<String, Integer> documentsViewCount = hazelcast.getMap(IMaps.DOCUMENTS_VIEW_COUNT);
		Integer viewCount = documentsViewCount.get(documentName) != null ? documentsViewCount.get(documentName) : 0;
		System.out.printf("Viewed %d times.%n", viewCount);

		IMap<String, Collection<String>> comments = hazelcast.getMap(IMaps.DOCUMENTS_COMMENTS);
		Collection<String> documentComments = comments.get(documentName);
		if (documentComments == null ) {
			System.out.println("Document has no comments yet.");
		} else {
			System.out.printf("Comments (%d):%n", documentComments.size());
			for (String comment: documentComments) {
				System.out.println(comment);
			}
		}
	}
	/**
	 * Add a comment about the current selected document.
	 */
	private void commentCommand() throws Exception {
		// I would love to use ifPresentOrElse here but lambda functions throwing exceptions is a big no-no apparently
		Optional<String> maybeSelectedDocument = getSelectedDocument();
		if (maybeSelectedDocument.isEmpty()) {
			System.out.println("No document selected!");
		} else {
			String selectedDocument = maybeSelectedDocument.get();
			System.out.println("Enter comment text:");
			String commentText = in.readLine();
			IMap<String, Collection<String>> comments = hazelcast.getMap(IMaps.DOCUMENTS_COMMENTS);
			// This is done atomically
			comments.executeOnKey(selectedDocument, new AddValueToCollectionProcessor<String, String>(commentText, new ArrayList<String>()));
			System.out.printf("Added a comment about %s.%n", selectedDocument);
		}
	}

	private Optional<String> getSelectedDocument() {
		IMap<String, String> selectedDocuments = hazelcast.getMap(IMaps.SELECTED_DOCUMENTS);
		return Optional.ofNullable(selectedDocuments.get(userName));
	}

	private void selectDocumentCommand() throws Exception {
		System.out.println("Enter document name:");
		String documentName = in.readLine();
		IMap<String, String> selectedDocuments = hazelcast.getMap(IMaps.SELECTED_DOCUMENTS);
		selectedDocuments.set(userName, documentName);
	}

	/*
	 * Main interactive user loop
	 */
	public void run() throws Exception {
		loop:
		while (true) {
			System.out.println("\nAvailable commands (type and press enter):");
			System.out.println(" s - select and show document");
			System.out.println(" i - show document view count and comments");
			System.out.println(" c - add comment");
			System.out.println(" a - add to favorites");
			System.out.println(" r - remove from favorites");
			System.out.println(" n - show next favorite");
			System.out.println(" l - list all favorites");
			System.out.println(" q - quit");
			// read first character
			int c = in.read();
			// throw away rest of the buffered line
			while (in.ready())
				in.read();
			switch (c) {
				case 'q': // Quit the application
					break loop;
				case 's': // Select and show a document
					selectDocumentCommand();
					showCommand();
					break;
				case 'i': // Show view count and comments of the selected document
					infoCommand();
					break;
				case 'c': // Add a comment to the selected document
					commentCommand();
					break;
				case 'a': // Add the selected document to favorites
					addFavoriteCommand();
					break;
				case 'r': // Remove the selected document from favorites
					removeFavoriteCommand();
					break;
				case 'n': // Select and show the next document in the list of favorites
					nextFavoriteCommand();
					break;
				case 'l': // Show the list of favorite documents
					listFavoritesCommand();
					break;
				case '\n':
				default:
					break;
			}
		}
	}

	/*
	 * Main method, creates a client instance and runs its loop
	 */
	public static void main(String[] args) {
		if (args.length != 1) {
			System.err.println("Usage: ./client <userName>");
			return;
		}
		try {
			Client client = new Client(args[0]);
			try {
				client.run();
			}
			finally {
				client.disconnect();
			}
		}
		catch (Exception e){
			e.printStackTrace();
		}
	}

}
