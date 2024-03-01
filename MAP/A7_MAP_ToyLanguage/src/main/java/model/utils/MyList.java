package model.utils;

import java.util.ArrayList;
import java.util.List;

public class MyList<T> implements MyIList<T> {
    private List<T> items;

    public MyList()
    {
        items = new ArrayList<>();
    }

    @Override
    public void add(T itemToAdd) {
        items.add(itemToAdd);
    }

    @Override
    public List<T> getItems() {
        return items;
    }

    @Override
    public String toString() {
        StringBuilder buf = new StringBuilder();
        for (T st : this.items)
        {
            buf.append(st);
            buf.append("\n");
        }
        // buf.append('\n');
        return buf.toString();

    }
}
