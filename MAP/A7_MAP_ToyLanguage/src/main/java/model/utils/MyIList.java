package model.utils;

import java.util.List;

public interface MyIList<T> {
    void add(T itemToAdd);
    List<T> getItems();
}
