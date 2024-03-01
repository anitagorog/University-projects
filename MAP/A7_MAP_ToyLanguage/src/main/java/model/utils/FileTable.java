package model.utils;

import java.util.HashMap;
import java.util.Map;

public class FileTable<K, V> implements IFileTable<K,V>{
    Map<K,V> fileTable;

    public FileTable() { fileTable = new HashMap<>(); }

    @Override
    public boolean isDefined(K key) {
        /*for(K k : this.fileTable.keySet())
        {
            if (k.equals(key))
                return true;
        }
        return false;*/
        return fileTable.containsKey(key); // needed hash not just equals for StringValue
    }

    @Override
    public void put(K key, V value) { fileTable.put(key, value); }

    @Override
    public V lookUp(K key) {
        return fileTable.get(key);
    }

    @Override
    public void delete(K key) {
        fileTable.remove(key);
    }

    public Map<K,V> getContent() {return fileTable;}

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        for(K k : this.fileTable.keySet())
        {
            s.append(k.toString()).append("\n");
        }
        // s.append('\n');
        return s.toString();
    }
}
