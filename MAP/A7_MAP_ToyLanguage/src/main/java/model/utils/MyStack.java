package model.utils;

import model.stmts.IStmt;

import java.util.*;

public class MyStack<T> implements MyIStack<T> {
    Stack<T> stack;
    // CollectionType<T> stack;

    public MyStack() {
        stack = new Stack<T>();
    }
    @Override
    public void push(T elem) {
        stack.push(elem);
    }

    @Override
    public T pop() {
        return stack.pop();
    }

    @Override
    public boolean isEmpty() {
        return stack.isEmpty();
    }

    @Override
    public List<T> getReverse() {
        List<T> auxList = Arrays.asList((T[])stack.toArray());
        Collections.reverse(auxList);
        return auxList;
    }

    @Override
    public String toString() {
        //return "stack " + getReverse();
        StringBuilder buf = new StringBuilder();
        for (T st : this.getReverse())
        {
            buf.append(st);
            buf.append("\n");
        }
        // buf.append('\n');
        return buf.toString();
    }
}
