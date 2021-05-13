import java.util.Random;
import java.util.Properties;

import javax.naming.Context;
import javax.naming.InitialContext;

import mwy.Searcher;

public class Main {
	// How many nodes and how many edges to create.
	private static final int GRAPH_NODES = 1000;
	private static final int GRAPH_EDGES = 2000;

	// How many searches to perform
	private static final int SEARCHES = 50;
	
	private static Searcher searcher;
	
	/**
	 * Creates nodes of a graph.
	 * @param nodeCount number of nodes to be created
	 */
	public static void createNodes(int nodeCount) {
		
		for (int i = 0; i < nodeCount; ++i) {
			searcher.addNode();
		}
	}
	
	/**
	 * Creates a randomly connected graph.
	 * @param edgeCount number of edges to be added
	 */
	public static void connectSomeNodes(int edgeCount) {
		for (int i = 0; i < edgeCount; ++i) {
			int nodeFromId = searcher.getRandomNodeId();
			int nodeToId = searcher.getRandomNodeId(); 
			searcher.connectNodes(nodeFromId, nodeToId);
		}
	}
	
	/**
	 * Runs a quick measurement on the graph.
	 * @param attemptCount number of searches
	 */
	public static void searchBenchmark(int attemptCount) {
		// Display measurement header.
		System.out.printf("%7s %8s %13s%n", "Attempt", "Distance", "Time");
		for (int i = 0; i < attemptCount; ++i) {
			// Select two random nodes.
			int nodeFromId = searcher.getRandomNodeId();
			int nodeToId = searcher.getRandomNodeId();

			// Calculate distance, timing the operation.
			long time = System.nanoTime();
			int distance = searcher.getDistance(nodeFromId, nodeToId);
			time = System.nanoTime() - time;
			
			// Print the measurement result.
			System.out.printf("%7d %8d %13d%n", i, distance, time / 1000);
		}        
	}

	public static void main(String[] args) throws Exception {

		Properties props = new Properties();
		props.put(Context.INITIAL_CONTEXT_FACTORY, "org.apache.openejb.client.RemoteInitialContextFactory");
		props.put(Context.PROVIDER_URL, "ejbd://127.0.0.1:4201");
		Context ctx = new InitialContext(props);
		searcher = (Searcher) ctx.lookup("SearcherImplRemote");

		if (args.length == 0) {
			System.out.println("No client id specified!");
			return;
		}
		int clientId = Integer.parseInt(args[0]);
		searcher.setClientId(clientId);

		if (!(args.length > 1 && "--search-only".equals(args[1]))) {
			System.out.println("Generating graph...");
			createNodes(GRAPH_NODES);
			connectSomeNodes(GRAPH_EDGES);
		}
		System.out.println("Searching...");
		searchBenchmark(SEARCHES);
	}
}
