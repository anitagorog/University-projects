package model.utils;

import java.util.HashMap;
import java.util.Map;

public class MyDictionary<K,V> implements MyIDictionary<K,V>{

    Map<K,V> dictionary;
    public MyDictionary() {
        dictionary = new HashMap<>();
    }
    @Override
    public boolean isDefined(K key) {
        return dictionary.containsKey(key);
    }

    @Override
    public void put(K key, V value) {
        dictionary.put(key, value);
    }

    @Override
    public V lookUp(K key) {
        return dictionary.get(key);
    }
    @Override
    public void update(K key, V value) {
        dictionary.put(key, value);
    }

    @Override
    public Map<K, V> getContent() {
        return this.dictionary;
    }

    public MyIDictionary<K, V> cloneSym()
    {
        MyIDictionary<K, V> symCopy = new MyDictionary<>();
        for(K key : dictionary.keySet())
            symCopy.put(key, dictionary.get(key));
        return symCopy;
    }

    @Override
    public String toString() {
        StringBuilder s = new StringBuilder();
        for(K k : this.dictionary.keySet())
        {
            s.append(k.toString()).append("->").append(this.dictionary.get(k).toString()).append("\n");
        }
        // s.append('\n');
        return s.toString();
    }
}
