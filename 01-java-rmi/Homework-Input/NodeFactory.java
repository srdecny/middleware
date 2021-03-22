import java.rmi.Remote;
import java.rmi.RemoteException;

public interface NodeFactory extends Remote {
    public Node createNode() throws RemoteException;
}