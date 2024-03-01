package model.exp;

import controller.MyException;
import model.types.BoolType;
import model.types.IntType;
import model.types.Type;
import model.utils.IHeapTable;
import model.utils.MyIDictionary;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.Value;

public class RelExp implements Exp{
    Exp e1;
    Exp e2;
    int op;
    // <  0
    // <= 1
    // == 2
    // != 3
    // >  4
    // >= 5

    public RelExp(Exp a, Exp b, int o)
    {
        e1 = a;
        e2 = b;
        op = o;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl, IHeapTable<Integer,Value> hp) throws MyException {
        Value nr = e1.eval(tbl, hp);
        Value nr2 = e2.eval(tbl, hp);
        if (nr.getType().equals(new IntType()))
        {
            if (nr2.getType().equals(new IntType()))
            {
                IntValue n1 = (IntValue) nr;
                IntValue n2 = (IntValue) nr2;
                if (op == 0) // <
                    return new BoolValue(n1.getVal() < n2.getVal());
                if (op == 1) // <=
                    return new BoolValue(n1.getVal() <= n2.getVal());
                if (op == 2) // ==
                    return new BoolValue(n1.getVal() == n2.getVal());
                if (op == 3) // !=
                    return new BoolValue(n1.getVal() != n2.getVal());
                if (op == 4) // >
                    return new BoolValue(n1.getVal() > n2.getVal());
                return new BoolValue(n1.getVal() >= n2.getVal());
            } else
                throw new MyException("Value not integer");
        } else
            throw new MyException("Value not integer");

    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typ1, typ2;
        typ1=e1.typecheck(typeEnv);
        typ2=e2.typecheck(typeEnv);
        if (typ1.equals(new IntType()))  {
            if (typ2.equals(new IntType())) {
                return new BoolType();
            } else throw new MyException("second operand is not an integer");
        } else throw new MyException("first operand is not an integer");
    }

    @Override
    public String toString() {
        String ops;
        if (op == 0)
            ops = "<";
        else if (op == 1)
            ops = "<=";
        else if (op == 2)
            ops = "==";
        else if (op == 3)
            ops = "!=";
        else if (op == 4)
            ops = ">=";
        else
            ops = ">=";
        return "RelExp{" +
                e1.toString() + ops +
                e2.toString() +
                '}';
    }
}
