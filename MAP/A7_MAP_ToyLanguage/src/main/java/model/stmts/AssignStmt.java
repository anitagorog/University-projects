package model.stmts;

import controller.MyException;
import model.ProgramState;
import model.exp.Exp;
import model.exp.ValueExp;
import model.types.Type;
import model.values.Value;
import model.utils.MyIDictionary;
import model.utils.MyIStack;

public class AssignStmt implements IStmt {
    String id;
    Exp exp;

    @Override
    public String toString() {
        return "AssignStmt{" +
                "id='" + id + '\'' +
                ", exp=" + exp +
                '}';
    }

    public AssignStmt(String v, Exp e) {
        id = v;
        exp = e;
    }

    @Override
    public ProgramState execute(ProgramState state) throws MyException {
        // MyIStack<IStmt> stk = state.getExeStack();
        MyIDictionary<String, Value> symTbl = state.getSymTable();
        if(symTbl.isDefined(id)) {
            try{
                Value val = exp.eval(symTbl, state.getHeapTable());
                Type typId = (symTbl.lookUp(id)).getType();
                if(val.getType().toString().equals(typId.toString())){
                    symTbl.update(id, val);
                }
                else throw new MyException("declared type of variable "+id+" and type of the assigned expression don't match");

            }
            catch (MyException e){
                throw new MyException(e.toString());
            }
            }
        else throw new MyException("the used variable"+id+" was not declared before");
        return null;
    }

    @Override
    public MyIDictionary<String, Type> typecheck(MyIDictionary<String, Type> typeEnv) throws MyException {
        Type typevar = typeEnv.lookUp(id);
        Type typexp = exp.typecheck(typeEnv);
        if (typevar.equals(typexp))
            return typeEnv;
        else
            throw new MyException("Assignment: right hand side and left hand side have different types ");
    }
}















