package view;

import controller.Controller;
import controller.MyException;
import model.*;
import model.exp.*;
import model.stmts.*;
import model.stmts.filestmts.closeRFileStmt;
import model.stmts.filestmts.openRFileStmt;
import model.stmts.filestmts.readFileStmt;
import model.types.BoolType;
import model.types.IntType;
import model.types.StringType;
import model.types.Type;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;
import repository.IRepository;
import repository.Repository;
import model.utils.*;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Objects;
import java.util.Scanner;


public class View {
    String logfile = "";
    private IStmt ex1= new CompStmt(new VarDeclStmt("v",new IntType()),
            new CompStmt(new AssignStmt("v",new ValueExp(new IntValue(2))),
                    new PrintStmt(new RelExp(new ValueExp(new IntValue(0)), new VarExp("v"), 1))));
    // checks that RelExp works
    private IStmt ex2 =  new CompStmt( new VarDeclStmt("a",new IntType()),
            new CompStmt(new VarDeclStmt("b",new IntType()),
                    new CompStmt(new AssignStmt("a", new ArithExp(1 ,new ValueExp(new IntValue(2)),
                            new ArithExp(3 ,new ValueExp(new IntValue(3)), new ValueExp(
                                    new IntValue(5))))), new CompStmt(new AssignStmt("b",
                                        new ArithExp(1 ,new VarExp("a"), new ValueExp(new IntValue(1)))),
                                            new PrintStmt(new VarExp("b"))))));
    private IStmt ex3 = new CompStmt(new VarDeclStmt("a",new BoolType()),
            new CompStmt(new VarDeclStmt("v", new IntType()),
                    new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                            new CompStmt(new IfStmt(new VarExp("a"),new AssignStmt("v",new ValueExp(new
                                    IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))),
                                            new PrintStmt(new VarExp("v"))))));

    private void printMenu(){
        System.out.println("0 - exit");
        System.out.println("1 - int v; v=2;Print(v) : "+ ex1);
        System.out.println("2 - int a;int b; a=2+3*5;b=a+1;Print(b)");
        System.out.println("3 - bool a; int v; a=true;(If a Then v=2 Else v=3);Print(v)");
        System.out.println("4 - add a new file");
        System.out.println("5 - test file statements");
    }
    public void run()
    {
        Scanner scannerFile = new Scanner(System.in);
        System.out.println("Enter the log file path: ");
        logfile = scannerFile.nextLine();
        while(true)
        {
            printMenu();
            Scanner scanner = new Scanner(System.in);
            System.out.println("Choose an option: ");
            String option = scanner.nextLine();
            switch (option) {
                case "0":
                    return;
                case "1":
                    this.executeEx1();
                    break;
                case "2":
                    this.executeEx2();
                    break;
                case "3":
                    this.executeEx3();
                    break;
                case "4":
                    scannerFile = new Scanner(System.in);
                    System.out.println("Enter the log file path: ");
                    logfile = scannerFile.nextLine();

                    // solve to put more

                    break;
                case "5":
                    execTest();
                    break;
            }
        }
    }

    private void execTest(){

        IStmt tes = new CompStmt(new VarDeclStmt("varF", new StringType()),
                new CompStmt(new AssignStmt("varF", new ValueExp(new StringValue("test.in"))),
                new CompStmt(new openRFileStmt(new VarExp("varF")),
                new CompStmt(new VarDeclStmt("varC", new IntType()) ,
                new CompStmt(new readFileStmt(new ValueExp(new StringValue("test.in")), "varC"),
                        new CompStmt(new PrintStmt(new VarExp("varC")),
                        new CompStmt(new readFileStmt(new ValueExp(new StringValue("test.in")), "varC"),
                        new CompStmt(new PrintStmt(new VarExp("varC")),
                        new closeRFileStmt(new ValueExp(new StringValue("test.in")))))))))));

        MyIStack<IStmt> stk = new MyStack<IStmt>();
        MyIDictionary<String, Value> symTbl = new MyDictionary<String,Value>();
        MyIList<Value> out = new MyList<Value>();
        FileTable<StringValue, BufferedReader> fileTab = new FileTable<>();
        HeapTable<Value> heapTable = new HeapTable<>();
        ProgramState crtPrgState= new ProgramState(stk, symTbl, out, tes, fileTab, heapTable);

        /*try {
            crtPrgState.addToFileTable(this.logfile);
        }
        catch (FileNotFoundException ex)
        {
            System.out.println(ex.getMessage());
        }*/

        IRepository repo = new Repository(this.logfile);
        repo.add(crtPrgState);
        Controller controller = new Controller(repo);
        try {
            controller.allStep();
        }
        catch (InterruptedException ex){
            System.out.println(ex.getMessage());
        }
    }

    private void executeEx1(){
        MyIStack<IStmt> stk = new MyStack<IStmt>();
        MyIDictionary<String, Value> symTbl = new MyDictionary<String,Value>();
        MyIList<Value> out = new MyList<Value>();
        FileTable<StringValue, BufferedReader> fileTab = new FileTable<>();
        HeapTable<Value> heapTable = new HeapTable<>();
        ProgramState crtPrgState= new ProgramState(stk, symTbl, out, ex1, fileTab, heapTable);

        /*try {
            crtPrgState.addToFileTable(this.logfile);
        }
        catch (FileNotFoundException ex)
        {
            System.out.println(ex.getMessage());
        }*/

        IRepository repo = new Repository(this.logfile);
        repo.add(crtPrgState);
        Controller controller = new Controller(repo);
        try {
            controller.allStep();
        }
        catch (InterruptedException ex){
            System.out.println(ex.getMessage());
        }
    }
    private void executeEx2(){
        MyIStack<IStmt> stk = new MyStack<IStmt>();
        MyIDictionary<String, Value> symTbl = new MyDictionary<String,Value>();
        MyIList<Value> out = new MyList<Value>();
        FileTable<StringValue, BufferedReader> fileTab = new FileTable<>();
        HeapTable<Value> heapTable = new HeapTable<>();
        ProgramState crtPrgState= new ProgramState(stk, symTbl, out, ex2, fileTab, heapTable);

        /*try {
            crtPrgState.addToFileTable(this.logfile);
        }
        catch (FileNotFoundException ex)
        {
            System.out.println(ex.getMessage());
        }*/

        IRepository repo = new Repository(this.logfile);
        repo.add(crtPrgState);
        Controller controller = new Controller(repo);
        try {
            controller.allStep();
        }
        catch (InterruptedException ex){
            System.out.println(ex.getMessage());
        }
    }
    private void executeEx3(){
        MyIStack<IStmt> stk = new MyStack<IStmt>();
        MyIDictionary<String, Value> symTbl = new MyDictionary<String,Value>();
        MyIList<Value> out = new MyList<Value>();
        FileTable<StringValue, BufferedReader> fileTab = new FileTable<>();
        HeapTable<Value> heapTable = new HeapTable<>();
        ProgramState crtPrgState= new ProgramState(stk, symTbl, out, ex3, fileTab, heapTable);

        /*try {
            crtPrgState.addToFileTable(this.logfile);
        }
        catch (FileNotFoundException ex)
        {
            System.out.println(ex.getMessage());
        }*/

        IRepository repo = new Repository(this.logfile);
        repo.add(crtPrgState);
        Controller controller = new Controller(repo);
        try {
            controller.allStep();
        }
        catch (InterruptedException ex){
            System.out.println(ex.getMessage());
        }
    }
}
