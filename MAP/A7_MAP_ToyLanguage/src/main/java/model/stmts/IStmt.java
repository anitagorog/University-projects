package model.stmts;

import controller.MyException;
import model.ProgramState;
import model.types.Type;
import model.utils.MyIDictionary;

public interface IStmt {
    public ProgramState execute(ProgramState state) throws MyException;
    MyIDictionary<String, Type> typecheck(MyIDictionary<String,Type> typeEnv) throws MyException;
}
