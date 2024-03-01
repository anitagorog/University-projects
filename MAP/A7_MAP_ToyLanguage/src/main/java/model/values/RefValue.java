package model.values;

import model.types.RefType;
import model.types.Type;

import java.util.Objects;

public class RefValue implements Value{
    int address;
    Type locationType;
    public RefValue(int addr, Type loctype) {
        address = addr;
        locationType = loctype;
    }

    @Override
    public boolean equals(Object another) {
        if (!(another instanceof RefValue another1))
            return false;
        return Objects.equals(this.address, another1.address);
    }

    @Override
    public int hashCode() {
        return Objects.hash(address, locationType);
    }

    @Override
    public Type getType() {
        //return new RefType();
        return new RefType(locationType);
    }
    public Type getInner() {
        return locationType;
    }
    public int getAddr() {
        return address;
    }

    public void setAddress(int addr) {
        address = addr;
    }

    @Override
    public String toString() {
        return "(" +
                address +
                ", " + locationType +
                ')';
    }
}
