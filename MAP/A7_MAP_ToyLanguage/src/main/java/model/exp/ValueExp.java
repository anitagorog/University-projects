package model.exp;

import controller.MyException;
import model.types.BoolType;
import model.types.IntType;
import model.types.Type;
import model.utils.IHeapTable;
import model.values.Value;
import model.utils.MyIDictionary;

import java.util.Objects;

public class ValueExp implements Exp {
    Value e;
    public ValueExp(Value v) {
        e = v;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl, IHeapTable<Integer,Value> hp) throws MyException {
        //System.out.println(e.getType().toString());
        if (Objects.equals(e.getType().toString(), "int"))
            return e;
        if (Objects.equals(e.getType().toString(), "bool"))
            return e;
        if (Objects.equals(e.getType().toString(), "string"))
            return e;
        return null;
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return e.getType();
    }

    @Override
    public String toString() {
        return "ValueExp{" +
                "e=" + e +
                '}';
    }
}
