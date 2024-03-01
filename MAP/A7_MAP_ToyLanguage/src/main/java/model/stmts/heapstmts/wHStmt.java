package model.stmts.heapstmts;

import controller.MyException;
import model.ProgramState;
import model.exp.Exp;
import model.stmts.IStmt;
import model.types.RefType;
import model.types.Type;
import model.utils.IHeapTable;
import model.utils.MyIDictionary;
import model.values.RefValue;
import model.values.Value;

public class wHStmt implements IStmt {
    String Var_Name;
    Exp expression; // new value that is going to be stored in the heap
    public wHStmt(String vn, Exp e) {
        Var_Name = vn;
        expression = e;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, Value> sym = state.getSymTable();
        IHeapTable<Integer, Value> heap = state.getHeapTable();
        if (!sym.isDefined(Var_Name))
            throw new MyException("Variable not defined");
        if (!(sym.lookUp(Var_Name).getType() instanceof RefType))
            throw new MyException("Variable not RefType");
        RefValue rv = (RefValue) sym.lookUp(Var_Name);
        if (!heap.isDefined(rv.getAddr()))
            throw new MyException("Address not found in heap");

        if (!expression.eval(sym, heap).getType().equals(rv.getInner()))
            throw new MyException("Type not matching from the heap");

        heap.put(rv.getAddr(), expression.eval(sym, heap));
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typevar = typeEnv.lookUp(Var_Name);
        Type typexp = expression.typecheck(typeEnv);
        if (typevar.equals(new RefType(typexp)))
            return typeEnv;
        else
            throw new MyException("wH stmt: right hand side and left hand side have different types ");

    }

    @Override
    public String toString() {
        return "wHStmt{" +
                "Var_Name='" + Var_Name + '\'' +
                ", expression=" + expression +
                '}';
    }
}
