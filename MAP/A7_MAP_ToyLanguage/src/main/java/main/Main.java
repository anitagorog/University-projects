package main;

import controller.Controller;
import controller.MyException;
import model.ProgramState;
import model.exp.*;
import model.stmts.*;
import model.stmts.heapstmts.newStmt;
import model.stmts.heapstmts.wHStmt;
import model.types.BoolType;
import model.types.IntType;
import model.types.RefType;
import model.types.Type;
import model.utils.*;
import model.values.BoolValue;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;
import repository.IRepository;
import repository.Repository;
import view.TextMenu;
import view.View;
import view.commands.ExitCommand;
import view.commands.RunExample;

import java.io.BufferedReader;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // View v = new View();
        // v.run();
        // Scanner scannerFile = new Scanner(System.in);
        // System.out.println("Enter the log file path: ");
        // String logfile = scannerFile.nextLine();

        TextMenu menu = new TextMenu();

        menu.addCommand(new ExitCommand("0", "exit"));

        IStmt ex1 = new CompStmt(new VarDeclStmt("v",new IntType()),
                new CompStmt(new AssignStmt("v",new ValueExp(new IntValue(2))),
                        new PrintStmt(new LogicExp(new ValueExp(new BoolValue(true)),
                                new ValueExp(new BoolValue(false)), 1))));
        try {
            ex1.typecheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> stk = new MyStack<IStmt>();
            MyIDictionary<String, Value> symTbl = new MyDictionary<String,Value>();
            MyIList<Value> out = new MyList<Value>();
            FileTable<StringValue, BufferedReader> fileTab = new FileTable<>();
            HeapTable<Value> heapTable = new HeapTable<>();
            ProgramState prg1 = new ProgramState(stk, symTbl, out, ex1, fileTab, heapTable);
            IRepository repo1 = new Repository(prg1, "log1.txt");
            Controller ctr1 = new Controller(repo1);
            menu.addCommand(new RunExample("1",ex1.toString(),ctr1));
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }

        IStmt ex2 = new CompStmt( new VarDeclStmt("a",new IntType()),
                new CompStmt(new VarDeclStmt("b",new IntType()),
                        new CompStmt(new AssignStmt("a", new ArithExp(1 ,new ValueExp(new IntValue(2)),
                                new ArithExp(3 ,new ValueExp(new IntValue(3)), new ValueExp(
                                        new IntValue(5))))), new CompStmt(new AssignStmt("b",
                                new ArithExp(1 ,new VarExp("a"), new ValueExp(new IntValue(1)))),
                                new PrintStmt(new VarExp("b"))))));
        try {
            ex2.typecheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> stk2 = new MyStack<IStmt>();
            MyIDictionary<String, Value> symTbl2 = new MyDictionary<String,Value>();
            MyIList<Value> out2 = new MyList<Value>();
            FileTable<StringValue, BufferedReader> fileTab2 = new FileTable<>();
            HeapTable<Value> heapTable2 = new HeapTable<>();
            ProgramState prg2 = new ProgramState(stk2, symTbl2, out2, ex2, fileTab2, heapTable2);
            IRepository repo2 = new Repository(prg2, "log2.txt");
            Controller ctr2 = new Controller(repo2);
            menu.addCommand(new RunExample("2",ex2.toString(),ctr2));
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }

        IStmt ex3 = new CompStmt(new VarDeclStmt("a",new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"),new AssignStmt("v",new ValueExp(new
                                        IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))),
                                        new PrintStmt(new VarExp("v"))))));
        try {
            ex3.typecheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> stk3 = new MyStack<IStmt>();
            MyIDictionary<String, Value> symTbl3 = new MyDictionary<String,Value>();
            MyIList<Value> out3 = new MyList<Value>();
            FileTable<StringValue, BufferedReader> fileTab3 = new FileTable<>();
            HeapTable<Value> heapTable3 = new HeapTable<>();
            ProgramState prg3 = new ProgramState(stk3, symTbl3, out3, ex3, fileTab3, heapTable3);
            IRepository repo3 = new Repository(prg3, "log3.txt");
            Controller ctr3 = new Controller(repo3);
            menu.addCommand(new RunExample("3",ex3.toString(),ctr3));
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }

        IStmt ex4 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new newStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new newStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new VarExp("v")),
                                                new PrintStmt(new VarExp("a")))))));
        try {
            ex4.typecheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> stk4 = new MyStack<IStmt>();
            MyIDictionary<String, Value> symTbl4 = new MyDictionary<String,Value>();
            MyIList<Value> out4 = new MyList<Value>();
            FileTable<StringValue, BufferedReader> fileTab4 = new FileTable<>();
            HeapTable<Value> heapTable4 = new HeapTable<>();
            ProgramState prg4 = new ProgramState(stk4, symTbl4, out4, ex4, fileTab4, heapTable4);
            IRepository repo4 = new Repository(prg4, "log.txt");
            Controller ctr4 = new Controller(repo4);
            menu.addCommand(new RunExample("4",ex4.toString(),ctr4));
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }

        IStmt ex5 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new newStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new newStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new rHExp(new VarExp("v"))),
                                                new PrintStmt(new ArithExp(1,
                                                        new rHExp(new rHExp(new VarExp("a"))),
                                                        new ValueExp(new IntValue(5)))))))));
        try {
            ex5.typecheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> stk5 = new MyStack<IStmt>();
            MyIDictionary<String, Value> symTbl5 = new MyDictionary<String,Value>();
            MyIList<Value> out5 = new MyList<Value>();
            FileTable<StringValue, BufferedReader> fileTab5 = new FileTable<>();
            HeapTable<Value> heapTable5 = new HeapTable<>();
            ProgramState prg5 = new ProgramState(stk5, symTbl5, out5, ex5, fileTab5, heapTable5);
            IRepository repo5 = new Repository(prg5, "log.txt");
            Controller ctr5 = new Controller(repo5);
            menu.addCommand(new RunExample("5",ex5.toString(),ctr5));
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }

        IStmt ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new newStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new PrintStmt(new rHExp(new VarExp("v"))),
                                new CompStmt(new wHStmt("v", new ValueExp(new IntValue(30))),
                                        new PrintStmt(new ArithExp(1, new rHExp(new VarExp("v")),
                                                new ValueExp(new IntValue(5))))))));
        try {
            ex6.typecheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> stk6 = new MyStack<IStmt>();
            MyIDictionary<String, Value> symTbl6 = new MyDictionary<String,Value>();
            MyIList<Value> out6 = new MyList<Value>();
            FileTable<StringValue, BufferedReader> fileTab6 = new FileTable<>();
            HeapTable<Value> heapTable6 = new HeapTable<>();
            ProgramState prg6 = new ProgramState(stk6, symTbl6, out6, ex6, fileTab6, heapTable6);
            IRepository repo6 = new Repository(prg6, "log.txt");
            Controller ctr6 = new Controller(repo6);
            menu.addCommand(new RunExample("6",ex6.toString(),ctr6));
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }

        IStmt ex7 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelExp(new VarExp("v"),
                                new ValueExp(new IntValue(0)), 4),
                                new CompStmt(new PrintStmt(new VarExp("v")),
                                        new AssignStmt("v", new ArithExp(2,
                                                new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v")))));
        try {
            ex7.typecheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> stk7 = new MyStack<IStmt>();
            MyIDictionary<String, Value> symTbl7 = new MyDictionary<String,Value>();
            MyIList<Value> out7 = new MyList<Value>();
            FileTable<StringValue, BufferedReader> fileTab7 = new FileTable<>();
            HeapTable<Value> heapTable7 = new HeapTable<>();
            ProgramState prg7 = new ProgramState(stk7, symTbl7, out7, ex7, fileTab7, heapTable7);
            IRepository repo7 = new Repository(prg7, "log.txt");
            Controller ctr7 = new Controller(repo7);
            menu.addCommand(new RunExample("7",ex7.toString(),ctr7));
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }

        IStmt ex8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new newStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new newStmt("v", new ValueExp(new IntValue(20))),
                                new PrintStmt(new rHExp(new VarExp("v"))))));
        try {
            ex8.typecheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> stk8 = new MyStack<IStmt>();
            MyIDictionary<String, Value> symTbl8 = new MyDictionary<String,Value>();
            MyIList<Value> out8 = new MyList<Value>();
            FileTable<StringValue, BufferedReader> fileTab8 = new FileTable<>();
            HeapTable<Value> heapTable8 = new HeapTable<>();
            ProgramState prg8 = new ProgramState(stk8, symTbl8, out8, ex8, fileTab8, heapTable8);
            IRepository repo8 = new Repository(prg8, "log.txt");
            Controller ctr8 = new Controller(repo8);
            menu.addCommand(new RunExample("8",ex8.toString(),ctr8));
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }

        IStmt ex9 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new newStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new newStmt("a", new VarExp("v")),
                                        new CompStmt(new newStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new rHExp(new rHExp(new VarExp("a")))))))));
        try {
            ex9.typecheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> stk9 = new MyStack<IStmt>();
            MyIDictionary<String, Value> symTbl9 = new MyDictionary<String,Value>();
            MyIList<Value> out9 = new MyList<Value>();
            FileTable<StringValue, BufferedReader> fileTab9 = new FileTable<>();
            HeapTable<Value> heapTable9 = new HeapTable<>();
            ProgramState prg9 = new ProgramState(stk9, symTbl9, out9, ex9, fileTab9, heapTable9);
            IRepository repo9 = new Repository(prg9, "log.txt");
            Controller ctr9 = new Controller(repo9);
            menu.addCommand(new RunExample("9",ex9.toString(),ctr9));
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }

        // FORK
        IStmt ex10 = new CompStmt(new VarDeclStmt("v", new IntType()), new CompStmt(
                new VarDeclStmt("a", new RefType(new IntType())), new CompStmt(
                        new AssignStmt("v", new ValueExp(new IntValue(10))), new CompStmt(
                                new newStmt("a", new ValueExp(new IntValue(22))), new CompStmt(
                                        new ForkStmt(new CompStmt(new wHStmt("a",
                                                new ValueExp(new IntValue(30))), new CompStmt(
                                                        new AssignStmt("v", new ValueExp(
                                                                new IntValue(32))), new CompStmt(
                                        new PrintStmt(new VarExp("v")), new PrintStmt(
                                                new rHExp(new VarExp("a")))
                                        ))))
                , new CompStmt(new PrintStmt(new VarExp("v")),
                new PrintStmt(new rHExp(new VarExp("a")))))))));
        try {
            ex10.typecheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> stk10 = new MyStack<IStmt>();
            MyIDictionary<String, Value> symTbl10 = new MyDictionary<String,Value>();
            MyIList<Value> out10 = new MyList<Value>();
            FileTable<StringValue, BufferedReader> fileTab10 = new FileTable<>();
            HeapTable<Value> heapTable10 = new HeapTable<>();
            ProgramState prg10 = new ProgramState(stk10, symTbl10, out10, ex10, fileTab10, heapTable10);
            IRepository repo10 = new Repository(prg10, "logFork.txt");
            Controller ctr10 = new Controller(repo10);
            menu.addCommand(new RunExample("10",ex10.toString(),ctr10));
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }

        IStmt exFork = new CompStmt(new VarDeclStmt("counter", new IntType()),
                new WhileStmt(new RelExp(new VarExp("counter"), new ValueExp(new IntValue(10)), 0),
                        new CompStmt(new ForkStmt(
                                new ForkStmt(
                                        new CompStmt(new VarDeclStmt("a", new IntType()), new CompStmt(
                                                new AssignStmt("a", new VarExp("counter")),
                                                new PrintStmt(new VarExp("a"))))
                                )
                        ), new AssignStmt("counter", new ArithExp(
                                1, new VarExp("counter"), new ValueExp(new IntValue(1))
                        ))))
        );
        try {
            exFork.typecheck(new MyDictionary<String, Type>());
            MyIStack<IStmt> stkF = new MyStack<IStmt>();
            MyIDictionary<String, Value> symTblF = new MyDictionary<String,Value>();
            MyIList<Value> outF = new MyList<Value>();
            FileTable<StringValue, BufferedReader> fileTabF = new FileTable<>();
            HeapTable<Value> heapTableF = new HeapTable<>();
            ProgramState prgF = new ProgramState(stkF, symTblF, outF, exFork, fileTabF, heapTableF);
            IRepository repoF = new Repository(prgF, "logFork.txt");
            Controller ctrF = new Controller(repoF);
            menu.addCommand(new RunExample("11",exFork.toString(),ctrF));
        } catch (MyException e) {
            System.out.println(e.getMessage());
        }

        menu.show();
    }
}