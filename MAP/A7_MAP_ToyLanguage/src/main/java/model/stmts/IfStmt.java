package model.stmts;

import controller.MyException;
import model.ProgramState;
import model.exp.Exp;
import model.types.BoolType;
import model.types.Type;
import model.utils.MyIDictionary;
import model.values.BoolValue;
import model.values.Value;

import java.util.Objects;

public class IfStmt implements IStmt {

    Exp exp;
    IStmt thenS;
    IStmt elseS;
    public IfStmt(Exp e, IStmt t, IStmt el){
        exp = e;
        thenS = t;
        elseS = el;
    }

    @Override
    public String toString() {
        return "(IF("+exp.toString()+")THEN("+thenS.toString()+")ELSE("+elseS.toString()+"))";
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        Value bv = exp.eval(state.getSymTable(), state.getHeapTable());
        // BoolValue bv = (BoolValue) v;
        // System.out.println(bv.toString());
        if (!(Objects.equals(bv.toString(), new BoolValue(true).toString()) || Objects.equals(bv.toString(), new BoolValue(false).toString())))
        {
            throw new MyException("Exp not boolean");
        }
        else if (Objects.equals(bv.toString(), new BoolValue(true).toString()))
        {
            thenS.execute(state);
        }
        else
            elseS.execute(state);
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typexp=exp.typecheck(typeEnv);
        if (typexp.equals(new BoolType())) {
            thenS.typecheck(typeEnv.cloneSym());
            elseS.typecheck(typeEnv.cloneSym());
            return typeEnv;
        }
        else
            throw new MyException("The condition of IF has not the type bool");
    }
}

























