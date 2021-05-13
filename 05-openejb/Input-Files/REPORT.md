The edge mapping was realized using ManyToMany annotation, which generates a joint table (a table with two node_int columns, where rows represent the edge).

Multiple graphs support was realized by adding a clientId property to the Node object, denoting the "owner" of the node. SearcherImpl then uses this clientId property in a WHERE clausule to operate only on the nodes (e.g. the graph) belonging to the user. 

Usage: 

Generating the graph and searching: java -cp "$OPENEJB_HOME/lib/*:example.jar:." Main <CLIENT_ID>
Only searching: java -cp "$OPENEJB_HOME/lib/*:example.jar:." Main <CLIENT_ID> --search-only