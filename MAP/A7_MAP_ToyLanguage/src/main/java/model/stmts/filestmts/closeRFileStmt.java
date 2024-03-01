package model.stmts.filestmts;

import controller.MyException;
import model.ProgramState;
import model.exp.Exp;
import model.stmts.IStmt;
import model.types.BoolType;
import model.types.StringType;
import model.types.Type;
import model.utils.MyIDictionary;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class closeRFileStmt implements IStmt {
    Exp exp;
    public closeRFileStmt(Exp e) { exp = e; }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        Value v = this.exp.eval(state.getSymTable(), state.getHeapTable());
        if (!(v.getType().equals(new StringType())))
            throw new MyException("Value is not StringType");
        StringValue sv = (StringValue) v;

        if (state.getFileTable().lookUp(sv) == null)                // ??
            throw new MyException("No BufferedReader associated");
        BufferedReader b = state.getFileTable().lookUp(sv);

        try {
            b.close();
        } catch (IOException e)
        {
            throw new MyException(e.getMessage());
        }

        state.getFileTable().delete(sv);

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typexp=exp.typecheck(typeEnv);
        if (typexp.equals(new StringType())) {
            return typeEnv;
        }
        else
            throw new MyException("The expression of closeRFile has not the type string");

    }

    @Override
    public String toString() {
        return "closeRFileStmt{" +
                "exp=" + exp +
                '}';
    }
}
