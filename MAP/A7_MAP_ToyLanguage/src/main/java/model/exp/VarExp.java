package model.exp;

import controller.MyException;
import model.types.Type;
import model.utils.IHeapTable;
import model.values.BoolValue;
import model.values.Value;
import model.utils.MyIDictionary;

public class VarExp implements Exp {
    String id;
    public VarExp(String v) {
        id = v;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl, IHeapTable<Integer,Value> hp) throws MyException {
        //System.out.println(tbl.lookUp(id).getType());
        //System.out.println(tbl.lookUp(id));

        return tbl.lookUp(id);
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return typeEnv.lookUp(id);
    }

    @Override
    public String toString() {
        return "VarExp{" +
                "id='" + id + '\'' +
                '}';
    }
}
