import com.hazelcast.map.*;
import java.util.Collection;
import java.util.Map;

public class AddValueToCollectionProcessor<K, V> implements EntryProcessor<K, Collection<V>, Object> {
    private V value;
    private Collection<V> emptyCollection;
    
    public AddValueToCollectionProcessor(V value, Collection<V> emptyCollection) {
        this.value = value;
        this.emptyCollection = emptyCollection;
    }

    @Override
    public Object process(Map.Entry<K, Collection<V>> entry) {
        Collection<V> collection;
        if (entry.getValue() == null) {
            collection = emptyCollection;
        } else {
            collection = entry.getValue();
        }
        collection.add(this.value);
        // The value has to be set manually, so Hazelcast knows it changed
        entry.setValue(collection);
        return null;
    }
}