package model.stmts;

import controller.MyException;
import model.ProgramState;
import model.exp.Exp;
import model.types.BoolType;
import model.types.Type;
import model.utils.MyIDictionary;
import model.values.BoolValue;

public class WhileStmt implements IStmt{
    Exp exp;
    IStmt stmt;
    public WhileStmt(Exp e, IStmt s) {
        exp = e;
        stmt = s;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        if (!(exp.eval(state.getSymTable(), state.getHeapTable()) instanceof BoolValue))
            throw new MyException("Expression did not return a BoolValue");
        BoolValue bv = (BoolValue) exp.eval(state.getSymTable(), state.getHeapTable());
        if (bv.getVal())
        {
            state.getExeStack().push(this);
            state.getExeStack().push(stmt);
        }
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typexp=exp.typecheck(typeEnv);
        if (typexp.equals(new BoolType())) {
            stmt.typecheck(typeEnv.cloneSym());
            return typeEnv;
        }
        else
            throw new MyException("The condition of WHILE has not the type bool");
    }

    @Override
    public String toString() {
        return "WhileStmt{" +
                "exp=" + exp +
                '}';
    }
}
