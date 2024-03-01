package model.stmts.filestmts;

import controller.MyException;
import model.ProgramState;
import model.exp.Exp;
import model.stmts.IStmt;
import model.types.IntType;
import model.types.StringType;
import model.types.Type;
import model.utils.MyIDictionary;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class readFileStmt implements IStmt {
    Exp exp;
    String var_name;
    public readFileStmt() {}
    public readFileStmt(Exp e, String v){
        exp = e;
        var_name = v;
    }
    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, Value> sym = state.getSymTable();
        if (!(sym.isDefined(this.var_name)))
            throw new MyException("Variable not defined in symbol table");
        if (!(sym.lookUp(this.var_name).getType().equals(new IntType())))
            throw new MyException("Variable not integer");
        Value val = this.exp.eval(sym, state.getHeapTable());
        if (!(val.getType().equals(new StringType())))
            throw new MyException("Value is not a StringType");
        StringValue v = (StringValue) val;
        if (state.getFileTable().lookUp(v) == null)                // ??
            throw new MyException("No BufferedReader associated");
        BufferedReader b = state.getFileTable().lookUp(v);

        String line;
        try {
            line = b.readLine();
        } catch (IOException e)
        {
            throw new MyException(e.getMessage());
        }
        IntValue iv;
        if (line == null)
        {
            iv = new IntValue(0);
        }
        else
            iv = new IntValue(Integer.parseInt(line));

        sym.put(this.var_name, iv);

        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typexp=exp.typecheck(typeEnv);
        if (typexp.equals(new StringType())) {
            return typeEnv;
        }
        else
            throw new MyException("The expression of readRFile has not the type string");
    }

    @Override
    public String toString() {
        return "readFileStmt{" +
                "exp=" + exp +
                ", var_name='" + var_name + '\'' +
                '}';
    }
}
