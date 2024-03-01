package model.stmts;

import controller.MyException;
import model.ProgramState;
import model.stmts.IStmt;
import model.types.Type;
import model.utils.MyIDictionary;

public class NopStmt implements IStmt {
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return null;
    }
}
