package model.exp;

import controller.MyException;
import model.types.RefType;
import model.types.Type;
import model.utils.IHeapTable;
import model.utils.MyIDictionary;
import model.values.RefValue;
import model.values.Value;

public class rHExp implements Exp{
    Exp exp;
    public rHExp(Exp e) {
        exp = e;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl, IHeapTable<Integer,Value> hp) throws MyException {
        if (!(exp.eval(tbl, hp).getType() instanceof RefType))
            throw new MyException("Type not RefType");

        RefValue rv = (RefValue) exp.eval(tbl, hp);
        int address = rv.getAddr();
        if (!hp.isDefined(address))
            throw new MyException("Address not valid");

        return hp.lookUp(address);
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typ=exp.typecheck(typeEnv);
        if (typ instanceof RefType) {
            RefType reft =(RefType) typ;
            return reft.getInner();
        } else
            throw new MyException("the rH argument is not a Ref Type");
    }

    @Override
    public String toString() {
        return "rHExp{" +
                "exp=" + exp +
                '}';
    }
}
