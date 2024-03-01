package model.utils;

import java.util.Map;

public interface IHeapTable<K, V> {
    boolean isDefined(K key);

    void put(K key, V value);
    V lookUp(K key);
    void delete(K key);

    void setContent(Map<K, V> integerValueMap);

    Map<K,V> getContent();
}
