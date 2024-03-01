package model.stmts;

import controller.MyException;
import model.ProgramState;
import model.exp.Exp;
import model.exp.VarExp;
import model.stmts.IStmt;
import model.types.Type;
import model.utils.MyIDictionary;
import model.utils.MyIList;
import model.values.Value;



public class PrintStmt implements IStmt {
    Exp exp;

    @Override
    public String toString() {
        return "PrintStmt{" +
                "exp=" + exp +
                '}';
    }


    public PrintStmt(Exp v) {
        exp = v;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {

        MyIList<Value> ot = state.getOut();
        ot.add(exp.eval(state.getSymTable(), state.getHeapTable()));
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        exp.typecheck(typeEnv);
        return typeEnv;
    }
}
