package model.values;

import model.types.IntType;
import model.types.Type;

import java.util.Objects;

public class IntValue implements Value {
    int val;
    public IntValue(int v) {
        val = v;
    }

    @Override
    public boolean equals(Object another) {
        if (!(another instanceof IntValue another1))
            return false;
        return Objects.equals(this.val, another1.val);
    }

    @Override
    public int hashCode() {
        return Objects.hash(val);
    }

    public int getVal() {return val;}

    public String toString() { return String.valueOf(val);}
    @Override
    public Type getType() {
        return new IntType();
    }
}
