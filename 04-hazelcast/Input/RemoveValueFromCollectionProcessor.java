import com.hazelcast.map.*;
import java.util.Collection;
import java.util.Map;

public class RemoveValueFromCollectionProcessor<K, V> implements EntryProcessor<K, Collection<V>, Object> {
    private V value;
    
    public RemoveValueFromCollectionProcessor(V value) {
        this.value = value;
    }

    @Override
    public Object process(Map.Entry<K, Collection<V>> entry) {
        Collection<V> collection;
        if (entry.getValue() == null) {
            return null;
        } else {
            collection = entry.getValue();
            collection.remove(this.value);
            // The value has to be set manually, so Hazelcast knows it changed
            entry.setValue(collection);
            return null;
        }
    }
}