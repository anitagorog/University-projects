package model.values;

import model.types.StringType;
import model.types.Type;

import java.util.Objects;

public class StringValue implements Value{
    String str;
    public StringValue(String s) { this.str = s; }

     @Override
    public boolean equals(Object another) {
         if (!(another instanceof StringValue another1))
             return false;
         return Objects.equals(this.str, another1.str);
    }
    @Override
    public int hashCode() {
        return Objects.hash(str);
    }

    public String getVal() { return str; }
    @Override
    public Type getType() {
        return new StringType();
    }
    @Override
    public String toString() {
        return str;
    }
}
