import com.hazelcast.map.*;
import java.util.Map;

public class IncrementDocumentViewProcessor implements EntryProcessor<String, Integer, Object> {
    @Override
    public Object process(Map.Entry<String, Integer> entry) {
        // Document was not viewed before
        if (entry.getValue() == null) {
            entry.setValue(0);
        }
        entry.setValue(entry.getValue() + 1);
        return null;
    }
}