package model.utils;

import java.util.Map;

public interface IFileTable<K, V> {
    boolean isDefined(K key);

    void put(K key, V value);
    V lookUp(K key);
    void delete(K key);

    Map<K,V> getContent();
}
