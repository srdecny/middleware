import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;

public class Server
{
	public static void main(String[] args){
		try {
			// Instantiate the remotely accessible object. The constructor
			// of the object automatically exports it for remote invocation.
            SearcherImpl searcher = new SearcherImpl();
			Searcher searcherStub = (Searcher) UnicastRemoteObject.exportObject(searcher, 0); 
			
			NodeFactoryImpl factory = new NodeFactoryImpl();
			NodeFactory factoryStub = (NodeFactory) UnicastRemoteObject.exportObject(factory, 0);
			
			// Use the registry on this host to register the server.
			// The host name must be changed if the server uses
			// another computer than the client!
            Naming.rebind("//localhost/RemoteSearcher", searcherStub);
            Naming.rebind("//localhost/RemoteNodeFactory", factoryStub);

			// The virtual machine will not exit here because the export of
			// the remotely accessible object creates a new thread that
			// keeps the application active.
		}
		catch (Exception e) {
			System.out.println("Server Exception: " + e.getMessage());
			e.printStackTrace();
		}
	} 
}