package model.stmts.heapstmts;

import controller.MyException;
import model.ProgramState;
import model.exp.Exp;
import model.stmts.IStmt;
import model.types.RefType;
import model.types.Type;
import model.utils.HeapTable;
import model.utils.MyIDictionary;
import model.values.RefValue;
import model.values.Value;

public class newStmt implements IStmt {
    String var_name;
    Exp expression;
    public newStmt(String var, Exp exp){
        var_name = var;
        expression = exp;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        if (!state.getSymTable().isDefined(var_name))
            throw new MyException("Variable not defined");
        if (!(state.getSymTable().lookUp(var_name).getType() instanceof RefType))
            throw new MyException("Variable not RefType");

        Value v = expression.eval(state.getSymTable(), state.getHeapTable());
        RefValue rv = (RefValue) state.getSymTable().lookUp(var_name);
        if (!v.getType().equals(rv.getInner()))
            throw new MyException("Type not matching");

        HeapTable<Value> heaptable = (HeapTable<Value>) state.getHeapTable();
        int free = heaptable.getFirstFree();
        heaptable.put(free, v);

        //rv.setAddress(free);
        RefValue rv1 = new RefValue(free, rv.getInner());
        state.getSymTable().update(var_name, rv1);

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typevar = typeEnv.lookUp(var_name);
        Type typexp = expression.typecheck(typeEnv);
        if (typevar.equals(new RefType(typexp)))
            return typeEnv;
        else
            throw new MyException("NEW stmt: right hand side and left hand side have different types ");
    }

    @Override
    public String toString() {
        return "new(" +
                var_name + ", " +
                expression +
                ')';
    }
}
