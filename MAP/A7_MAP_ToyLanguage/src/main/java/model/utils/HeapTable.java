package model.utils;

import java.util.HashMap;
import java.util.Map;

public class HeapTable<V> implements IHeapTable<Integer, V>{
    Map<Integer,V> heapTable;
    int firstFree;
    public HeapTable() {
        heapTable = new HashMap<>();
        firstFree = 1;
    }
    public int getFirstFree() {
        return firstFree;
    }

    void changeFirstFree() {
        firstFree++;
    }

    @Override
    public boolean isDefined(Integer key) {
        return heapTable.containsKey(key);
    }

    @Override
    public void put(Integer key, V value) {
        heapTable.put(key, value);
        changeFirstFree();
    }

    @Override
    public V lookUp(Integer key) {
        return heapTable.get(key);
    }

    @Override
    public void delete(Integer key) {
        heapTable.remove(key);
    }

    @Override
    public void setContent(Map<Integer, V> integerValueMap) {
        this.heapTable = integerValueMap;
    }

    @Override
    public Map<Integer, V> getContent() {
        return this.heapTable;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        for(Integer k : this.heapTable.keySet())
        {
            s.append(k.toString()).append("->").append(this.heapTable.get(k).toString()).append("\n");
        }
        // s.append('\n');
        return s.toString();
    }
}
