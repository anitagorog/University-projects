package model.stmts.filestmts;

import controller.MyException;
import model.ProgramState;
import model.exp.Exp;
import model.stmts.IStmt;
import model.types.StringType;
import model.types.Type;
import model.utils.IFileTable;
import model.utils.MyIDictionary;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

public class openRFileStmt implements IStmt {
    Exp exp;
    public openRFileStmt() {}
    public openRFileStmt(Exp e) { this.exp = e; }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String,Value> sym = state.getSymTable();
        IFileTable<StringValue,BufferedReader> fileT = state.getFileTable();
        Value val = this.exp.eval(sym, state.getHeapTable());
        if (!(val.getType().equals(new StringType())))
            throw new MyException("Value is not StringType");
        if (fileT.isDefined((StringValue) val))
            throw new MyException("Key already exists in FileTable");
        StringValue v = (StringValue) val;

        BufferedReader b = null;
        try {
            b = new BufferedReader(new FileReader(v.getVal()));
        } catch (FileNotFoundException e) {
            throw new MyException(e.getMessage());
        }

        fileT.put(v, b);

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typexp=exp.typecheck(typeEnv);
        if (typexp.equals(new StringType())) {
            return typeEnv;
        }
        else
            throw new MyException("The expression of openRFile has not the type string");
    }

    @Override
    public String toString() {
        return "openRFileStmt{" +
                "exp=" + exp +
                '}';
    }
}
