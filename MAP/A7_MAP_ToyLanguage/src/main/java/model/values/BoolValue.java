package model.values;

import model.types.BoolType;
import model.types.IntType;
import model.types.Type;

import java.util.Objects;

public class BoolValue implements Value {
    boolean bool;
    public BoolValue(Boolean b)
    {
        bool = b;
    }

    @Override
    public boolean equals(Object another) {
        if (!(another instanceof BoolValue another1))
            return false;
        return Objects.equals(this.bool, another1.bool);
    }

    @Override
    public int hashCode() {
        return Objects.hash(bool);
    }

    @Override
    public Type getType() {
        return new BoolType();
    }

    public String toString() { return String.valueOf(bool);}
    public boolean getVal() {return bool;}
}
