package model.exp;

import controller.MyException;
import model.types.BoolType;
import model.types.IntType;
import model.types.Type;
import model.utils.IHeapTable;
import model.values.BoolValue;
import model.values.Value;
import model.utils.MyIDictionary;

import java.util.Objects;

public class LogicExp implements Exp {
    Exp e1;
    Exp e2;
    int op;
    public LogicExp(Exp a, Exp b, int o)
    {
        e1 = a;
        e2 = b;
        op = o;
    }
    @Override
    public Value eval(MyIDictionary<String, Value> tbl, IHeapTable<Integer,Value> hp) throws MyException {
        Value nr = e1.eval(tbl, hp);
        Value nr2 = e2.eval(tbl, hp);
        if (Objects.equals(nr.getType(), new BoolType()))
        {
            if (Objects.equals(nr2.getType(), new BoolType()))
            {
                BoolValue n = (BoolValue) nr;
                BoolValue n2 = (BoolValue) nr2;
                return new BoolValue(n.getVal() && n2.getVal());
                // and || ?
            }
            else throw new MyException("e1 not bool");
        }
        else throw new MyException("e2 not bool");
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typ1, typ2;
        typ1=e1.typecheck(typeEnv);
        typ2=e2.typecheck(typeEnv);
        if (typ1.equals(new BoolType()))  {
            if (typ2.equals(new BoolType())) {
                return new BoolType();
            } else throw new MyException("second operand is not a boolean");
        } else throw new MyException("first operand is not a boolean");
    }

    @Override
    public String toString() {
        String ops;
        if (op == 1)
            ops = "&&";
        else
            ops = "||";
        return "LogicExp{" +
                  e1.toString() + ops+
                  e2.toString() +
                '}';
    }
}


















