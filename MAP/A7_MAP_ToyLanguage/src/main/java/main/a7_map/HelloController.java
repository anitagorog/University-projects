package main.a7_map;

import controller.Controller;
import controller.MyException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.stage.Stage;
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
import model.values.Value;
import repository.IRepository;
import repository.Repository;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class HelloController {
    @FXML
    private ListView<IStmt> programsListView;

    @FXML
    private Button MyButton;

    @FXML
    private Label MyLabel;

    //private RunController runController = new RunController();

    //@FXML
    //protected void onHelloButtonClick() { welcomeText.setText("Welcome to JavaFX Application!"); }

    @FXML
    public void initialize() {
        MyLabel.setText("Select a program");
        programsListView.setItems(getAllStmts());
        // MyButton.setOnAction(event -> runProgram());
        //
    }

    @FXML
    private void runProgram() {
        IStmt selectedStmt = programsListView.getSelectionModel().getSelectedItem();
        if (selectedStmt == null) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error!");
            alert.setContentText("No Statement selected!");
            alert.showAndWait();
        } else {
            int id = programsListView.getSelectionModel().getSelectedIndex();
            try {
                selectedStmt.typecheck(new MyDictionary<String, Type>());
                ProgramState programState = new ProgramState(new MyStack<IStmt>(), new MyDictionary<String, Value>(), new MyList<Value>(), selectedStmt, new FileTable<>(), new HeapTable<>());
                IRepository repository = new Repository(programState, "log" + (id + 1) + ".txt");
                Controller controller = new Controller(repository);
                //runController.setController(controller);
                // --------------------------------------------------------------------------
                FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("run-view.fxml"));
                //fxmlLoader.setLocation(HelloApplication.class.getResource("run-view.fxml"));
                //Parent programExecutorRoot = fxmlLoader.load();
                Scene scene = new Scene(fxmlLoader.load(), 800, 500);
                //---
                RunController runController = fxmlLoader.getController();
                runController.setController(controller);
                //--
                Stage stage = new Stage();
                stage.setTitle("Execution");
                stage.setScene(scene);
                stage.show();
            } catch (MyException exception) {
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error encountered!");
                alert.setContentText(exception.getMessage());
                alert.showAndWait();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

    @FXML
    private ObservableList<IStmt> getAllStmts() {
        List<IStmt> allStmts = new ArrayList<>();

        IStmt ex1 = new CompStmt(new VarDeclStmt("v",new IntType()),
                new CompStmt(new AssignStmt("v",new ValueExp(new IntValue(2))),
                        new PrintStmt(new LogicExp(new ValueExp(new BoolValue(true)),
                                new ValueExp(new BoolValue(false)), 1))));
        allStmts.add(ex1);

        IStmt ex2 = new CompStmt( new VarDeclStmt("a",new IntType()),
                new CompStmt(new VarDeclStmt("b",new IntType()),
                        new CompStmt(new AssignStmt("a", new ArithExp(1 ,new ValueExp(new IntValue(2)),
                                new ArithExp(3 ,new ValueExp(new IntValue(3)), new ValueExp(
                                        new IntValue(5))))), new CompStmt(new AssignStmt("b",
                                new ArithExp(1 ,new VarExp("a"), new ValueExp(new IntValue(1)))),
                                new PrintStmt(new VarExp("b"))))));
        allStmts.add(ex2);

        IStmt ex3 = new CompStmt(new VarDeclStmt("a",new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"),new AssignStmt("v",new ValueExp(new
                                        IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))),
                                        new PrintStmt(new VarExp("v"))))));
        allStmts.add(ex3);

        IStmt ex4 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new newStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new newStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new VarExp("v")),
                                                new PrintStmt(new VarExp("a")))))));
        allStmts.add(ex4);

        IStmt ex5 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new newStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new newStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new rHExp(new VarExp("v"))),
                                                new PrintStmt(new ArithExp(1,
                                                        new rHExp(new rHExp(new VarExp("a"))),
                                                        new ValueExp(new IntValue(5)))))))));
        allStmts.add(ex5);

        IStmt ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new newStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new PrintStmt(new rHExp(new VarExp("v"))),
                                new CompStmt(new wHStmt("v", new ValueExp(new IntValue(30))),
                                        new PrintStmt(new ArithExp(1, new rHExp(new VarExp("v")),
                                                new ValueExp(new IntValue(5))))))));
        allStmts.add(ex6);

        IStmt ex7 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelExp(new VarExp("v"),
                                new ValueExp(new IntValue(0)), 4),
                                new CompStmt(new PrintStmt(new VarExp("v")),
                                        new AssignStmt("v", new ArithExp(2,
                                                new VarExp("v"), new ValueExp(new IntValue(1)))))),
                                new PrintStmt(new VarExp("v")))));
        allStmts.add(ex7);

        IStmt ex8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new newStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new newStmt("v", new ValueExp(new IntValue(20))),
                                new PrintStmt(new rHExp(new VarExp("v"))))));
        allStmts.add(ex8);

        IStmt ex9 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new newStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new newStmt("a", new VarExp("v")),
                                        new CompStmt(new newStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new rHExp(new rHExp(new VarExp("a")))))))));
        allStmts.add(ex9);

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
        allStmts.add(ex10);

        IStmt ex11 = new CompStmt(new VarDeclStmt("counter", new IntType()),
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
        allStmts.add(ex11);

        return FXCollections.observableArrayList(allStmts);
    }
}