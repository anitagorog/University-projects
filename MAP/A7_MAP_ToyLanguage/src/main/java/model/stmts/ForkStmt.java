package model.stmts;

import controller.MyException;
import model.ProgramState;
import model.types.Type;
import model.utils.MyDictionary;
import model.utils.MyIDictionary;
import model.utils.MyIStack;
import model.utils.MyStack;
import model.values.Value;

public class ForkStmt implements IStmt{
    IStmt stmt;
    public ForkStmt(IStmt st)
    {
        this.stmt = st;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, Value> sym = state.getSymTable().cloneSym(); // needed to put in Idict too
        MyIStack<IStmt> stk = new MyStack<IStmt>();

        return new ProgramState(stk, sym, state.getOut(), stmt, state.getFileTable(),
                state.getHeapTable(), state.getNextId());
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        return stmt.typecheck(typeEnv);
    }

    @Override
    public String toString() {
        return "ForkStmt{" +
                "stmt=" + stmt +
                '}';
    }
}
