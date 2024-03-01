package model.stmts;

import controller.MyException;
import model.ProgramState;
import model.types.Type;
import model.utils.MyIDictionary;
import model.utils.MyIStack;

public class CompStmt implements IStmt {
    
    IStmt first;
    IStmt snd;

    public CompStmt(IStmt f, IStmt s) {
        this.first = f;
        this.snd = s;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIStack<IStmt> stk = state.getExeStack();
        stk.push(snd);
        stk.push(first);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        //MyIDictionary<String,Type> typEnv1 = first.typecheck(typeEnv);
        //MyIDictionary<String,Type> typEnv2 = snd.typecheck(typEnv1);
        //return typEnv2;
        return snd.typecheck(first.typecheck(typeEnv));
    }

    @Override
    public String toString() {
        return "CompStmt{" +
                "first=" + first +
                ", snd=" + snd +
                '}';
    }
}
