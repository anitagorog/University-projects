package model;

import controller.MyException;
import model.stmts.IStmt;
import model.types.Type;
import model.utils.*;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;

public class ProgramState {
    int id;
    static int lastid = 0; // increment when making the thread with getNextId
    public static synchronized int getNextId() {
        lastid++; return lastid;
    }
    // public int getId() {return id;}
    MyIStack<IStmt> exeStack;
    MyIDictionary<String, Value> symTable;
    MyIList<Value> out;
    IFileTable<StringValue, BufferedReader> fileTable;
    IHeapTable<Integer, Value> heapTable;
    IStmt originalProgram; //optional field, but good to have

    public int getId() {return id;}

    public ProgramState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symTbl, MyIList<Value> ot,
                        IStmt prg, IFileTable<StringValue, BufferedReader> fileTab,
                        IHeapTable<Integer, Value> heapT)
    {
        exeStack = stk;
        symTable = symTbl;
        out = ot;
        fileTable = fileTab;
        heapTable = heapT;
        originalProgram = prg; // !!!
        // originalProgram = deepCopy(prg); // recreate the entire original prg
        stk.push(prg);
    }

    public ProgramState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symTbl, MyIList<Value> ot,
                        IStmt prg, IFileTable<StringValue, BufferedReader> fileTab,
                        IHeapTable<Integer, Value> heapT, int ID)
    {
        id = ID;
        exeStack = stk;
        symTable = symTbl;
        out = ot;
        fileTable = fileTab;
        heapTable = heapT;
        originalProgram = prg; // !!!
        // originalProgram = deepCopy(prg); // recreate the entire original prg
        stk.push(prg);
    }

    public Boolean isNotCompleted()
    {
        return !(this.exeStack.isEmpty()); // true when exe not empty
    }
    public ProgramState oneStep() throws MyException {
        if(exeStack.isEmpty())
            throw new MyException("Program state stack is empty");
        IStmt crtStmt = exeStack.pop();
        return crtStmt.execute(this);
    }

    public MyIStack<IStmt> getExeStack() {
        return exeStack;
    }

    public void setExeStack(MyIStack<IStmt> exeStack) {
        this.exeStack = exeStack;
    }

    public MyIDictionary<String, Value> getSymTable() {
        return symTable;
    }

    public void setSymTable(MyIDictionary<String, Value> symTable) {
        this.symTable = symTable;
    }

    public MyIList<Value> getOut() {
        return out;
    }

    public void setOut(MyIList<Value> out) {
        this.out = out;
    }

    public IFileTable<StringValue, BufferedReader> getFileTable() { return this.fileTable; }

    public IHeapTable<Integer, Value> getHeapTable() { return heapTable; }

    public void addToFileTable(String str) throws FileNotFoundException {
        StringValue sv = new StringValue(str);
        BufferedReader bf = new BufferedReader(new InputStreamReader(new FileInputStream(str)));
        if (!(this.fileTable.isDefined(sv))) {
            this.fileTable.put(sv, bf);
        }
    }

    public IStmt getOriginalProgram() {
        return originalProgram;
    }

    public void setOriginalProgram(IStmt originalProgram) {
        this.originalProgram = originalProgram;
    }

    @Override
    public String toString() {
        return "ID:" + id + '\n' +
                "ExeStack:\n" + exeStack +
                "SymTable:\n" + symTable +
                "Out:\n" + out +
                "FileTable:\n" + fileTable +
                "HeapTable:\n" + heapTable +
                "\n";
    }
}