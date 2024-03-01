package model.utils;

import java.util.List;

public interface MyIStack<T> {
    void push(T elem);
    T pop();
    boolean isEmpty();
    List<T> getReverse();
}
