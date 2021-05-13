package mwy;

import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.ManyToOne;
import javax.persistence.OneToMany;
import javax.persistence.ManyToMany;
import javax.persistence.JoinTable;
import javax.persistence.JoinColumn;

@Entity
public class Node {
	private int id;
	
	@Id @GeneratedValue(strategy=GenerationType.AUTO)
	public int getId() {
		return this.id;
	}

	// In this field the client ID is stored
	// Searcher uses this field to filter through the nodes, so it works on a client's graph
	private int clientId;

	public int getClientId() {
		return this.clientId;
	}

	public void setClientId(int clientId) {
		this.clientId = clientId;
	}

	public void setId(int id) {
		this.id = id;
	}
	
	/* The set of nodes connected to this node by an edge. */
	private Collection<Node> neighbors = new HashSet<Node>();
	
	@ManyToMany
	public Collection<Node> getNeighbors() {
		return this.neighbors;
	}

	public void setNeighbors(Collection<Node> neighbors) {
		this.neighbors = neighbors;
	}

	public Node(int clientId) {
		this.neighbors = new HashSet<Node>();
		this.clientId = clientId;
	}

	public void addNeighbor(Node neighbor) {
		getNeighbors().add(neighbor);
	}
}
