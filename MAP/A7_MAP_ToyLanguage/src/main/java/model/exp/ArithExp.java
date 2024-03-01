package model.exp;

import controller.MyException;
import model.types.IntType;
import model.types.Type;
import model.utils.IHeapTable;
import model.values.IntValue;
import model.values.Value;
import model.utils.MyIDictionary;

public class ArithExp implements Exp {
    Exp e1;
    Exp e2;
    int op; //1-plus, 2-minus, 3-star, 4-divide

    public ArithExp(int c, Exp Exp1, Exp Exp2) {
        e1 = Exp1;
        e2 = Exp2;
        op = c;
    }


    @Override
    public Value eval(MyIDictionary<String, Value> tbl, IHeapTable<Integer,Value> hp) throws MyException {
        Value v1, v2;
        v1 = e1.eval(tbl, hp);
        if (v1.getType().toString().equals(new IntType().toString())) {
            v2 = e2.eval(tbl, hp);
            if (v2.getType().toString().equals(new IntType().toString())) {
                IntValue i1 = (IntValue) v1;
                IntValue i2 = (IntValue) v2;
                int n1, n2;
                n1 = i1.getVal();
                n2 = i2.getVal();
                if (op == 1) return new IntValue(n1 + n2);
                if (op == 2) return new IntValue(n1 - n2);
                if (op == 3) return new IntValue(n1 * n2);
                if (op == 4) {
                    if (n2 == 0) throw new MyException("division by zero");
                    else return new IntValue(n1 / n2);
                }
            } else
                throw new MyException("second operand is not an integer");
        } else
            throw new MyException("first operand is not an integer");
        return v1;  // ?
    }

    @Override
    public Type typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typ1, typ2;
        typ1=e1.typecheck(typeEnv);
        typ2=e2.typecheck(typeEnv);
        if (typ1.equals(new IntType()))  {
            if (typ2.equals(new IntType())) {
                return new IntType();
            } else throw new MyException("second operand is not an integer");
        }else throw new MyException("first operand is not an integer");
    }

    @Override
    public String toString() {
        return "ArithExp{" +
                "e1=" + e1 +
                ", e2=" + e2 +
                ", op=" + op +
                '}';
    }
}















