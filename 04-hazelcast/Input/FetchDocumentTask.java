import java.io.Serializable;
import java.util.concurrent.*;
import com.hazelcast.core.*;
import com.hazelcast.map.*;

public class FetchDocumentTask implements Callable<Document>, Serializable, HazelcastInstanceAware {
    private transient HazelcastInstance hazelcastInstance;
    private String documentName;

    public void setHazelcastInstance( HazelcastInstance hazelcastInstance ) {
        this.hazelcastInstance = hazelcastInstance;
    }
    public FetchDocumentTask(String documentName) {
        this.documentName = documentName;
    }

    @Override
    public Document call() throws Exception {
        IMap<String, Document> documents = hazelcastInstance.getMap(IMaps.DOCUMENTS);
        Document document = documents.get(documentName);
        if (document == null) {
            Document generatedDocument = DocumentGenerator.generateDocument(this.documentName);
            documents.set(documentName, generatedDocument);
            return generatedDocument;
        } else {
            return document;
        }
    }
}
