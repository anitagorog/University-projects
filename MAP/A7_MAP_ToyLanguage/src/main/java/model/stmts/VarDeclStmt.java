package model.stmts;

import controller.MyException;
import model.ProgramState;
import model.types.IntType;
import model.types.Type;
import model.utils.MyIDictionary;
import model.utils.MyIStack;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.Value;

public class VarDeclStmt implements IStmt{
    String name;
    Type typ;
    public VarDeclStmt(String v, Type type) {
        typ = type;
        name = v;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        MyIDictionary<String, Value> d = state.getSymTable();
        if (!d.isDefined(name))
        {
            d.put(name, this.typ.defaultValue());
        }
        else throw new MyException("Already declared");
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        typeEnv.put(name,typ);
        return typeEnv;
    }

    @Override
    public String toString() {
        return "VarDeclStmt{" +
                "name='" + name + '\'' +
                ", typ=" + typ +
                '}';
    }
}
