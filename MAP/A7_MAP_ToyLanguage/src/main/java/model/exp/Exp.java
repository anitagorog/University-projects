package model.exp;

import controller.MyException;
import model.types.Type;
import model.utils.IHeapTable;
import model.values.Value;
import model.utils.MyIDictionary;

public interface Exp {
    Value eval(MyIDictionary<String,Value> tbl, IHeapTable<Integer,Value> hp) throws MyException;
    Type typecheck(MyIDictionary<String,Type> typeEnv) throws MyException;
}
