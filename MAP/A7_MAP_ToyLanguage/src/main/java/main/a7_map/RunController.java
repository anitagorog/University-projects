package main.a7_map;
// needed to change RunView to RunController ! in line
// fx:controller="main.a7_map.RunController"

import controller.Controller;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.scene.control.*;
//import javafx.util.Pair;
import javafx.scene.input.MouseEvent;
import model.ProgramState;
import model.stmts.IStmt;
import model.values.IntValue;
import model.values.StringValue;
import model.values.Value;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

class Pair<T1, T2> {
    T1 first;
    T2 second;

    public Pair(T1 first, T2 second) {
        this.first = first;
        this.second = second;
    }
}


public class RunController {
    @FXML
    private TextField PrgStateNumberField;

    @FXML
    private TableView<Pair<Integer, Value>> HeapTable;

    @FXML
    private TableColumn<Pair<Integer, Value>, Integer> address;

    @FXML
    private TableColumn<Pair<Integer, Value>, String> value;

    @FXML
    private ListView<Value> Out;

    @FXML
    private ListView<String> FileTable;

    @FXML
    private ListView<Integer> PrgIds;

    @FXML
    private TableView<Pair<String, Value>> SymTable;

    @FXML
    private TableColumn<Pair<String, Value>, String> SymName;

    @FXML
    private TableColumn<Pair<String, Value>, String> SymValue;

    @FXML
    private ListView<IStmt> ExeStack;

    @FXML
    private Button oneStepButton;

    Controller controller;

    public RunController() {}

    public void setController(Controller controller) {
        this.controller = controller;
        this.populate();

    }

    @FXML
    public void initialize() {
        address.setCellValueFactory(p -> new SimpleIntegerProperty(p.getValue().first).asObject());
        value.setCellValueFactory(p -> new SimpleStringProperty( p.getValue().second.toString() ));
        SymName.setCellValueFactory(p -> new SimpleStringProperty( p.getValue().first.toString() ));
        SymValue.setCellValueFactory(p -> new SimpleStringProperty( p.getValue().second.toString() ));
    }

    @FXML
    public void populate() {
        PrgStateNumberField.setText(controller.getNumberOfPrgStates());
        populateHeapTable();
        populateSymTable(); // PrgState whose ID has been selected from Ids
        populateOut();
        populateFile();
        populateIds();
        populateExe(); // PrgState whose ID has been selected from Ids
    }

    private void populateHeapTable() {
        ProgramState programState = getCurrentPrg();
        Map<Integer, Value> heap = Objects.requireNonNull(programState).getHeapTable().getContent();
        //heap.put(1, new IntValue(2));
        ArrayList<Pair<Integer, Value>> heapEntries = new ArrayList<>();
        for (Map.Entry<Integer, Value> entry : heap.entrySet()) {
            heapEntries.add(new Pair<>(entry.getKey(), entry.getValue()));
        }
        HeapTable.setItems(FXCollections.observableArrayList(heapEntries));
    }

    private void populateSymTable() {
        ProgramState programState = getCurrentPrg();
        Map<String, Value> heap = Objects.requireNonNull(programState).getSymTable().getContent();
        ArrayList<Pair<String, Value>> entries = new ArrayList<>();
        //entries.add(new Pair<>("a", new IntValue(4)));
        for (Map.Entry<String, Value> entry : heap.entrySet()) {
            entries.add(new Pair<>(entry.getKey(), entry.getValue()));
        }
        SymTable.setItems(FXCollections.observableArrayList(entries));
    }

    private void populateOut() {
        ProgramState programState = getCurrentPrg();
        List<Value> out = programState.getOut().getItems();
        //out.add(new IntValue(3));
        Out.setItems(FXCollections.observableArrayList(out));
    }

    private void populateFile() {
        ProgramState programState = getCurrentPrg();
        Map<StringValue, BufferedReader> fileTable = programState.getFileTable().getContent();
        //fileTable.put(new StringValue("aa"), null);
        ArrayList<String> entries = new ArrayList<>();
        for (Map.Entry<StringValue, BufferedReader> entry : fileTable.entrySet()) {
            entries.add(entry.getKey().toString() + " - " + entry.getValue());
        }

        FileTable.setItems(FXCollections.observableArrayList(entries));
    }

    private void populateIds() {
        List<ProgramState> prgStates = controller.getPrgStates();
        List<Integer> idList = new ArrayList<>();
        for (ProgramState i : prgStates)
        {
            idList.add(i.getId());
        }
        //idList.add(2);
        PrgIds.setItems(FXCollections.observableList(idList));

        PrgStateNumberField.setText(controller.getNumberOfPrgStates());
    }

    private void populateExe() {
        ProgramState programState = getCurrentPrg();
        List<IStmt> exe = programState.getExeStack().getReverse();
        ExeStack.setItems(FXCollections.observableList(exe));
    }

    private ProgramState getCurrentPrg(){
        if (controller.getNumberOfPrgStates().equals("0"))
            return null;
        else {
            int currentId = PrgIds.getSelectionModel().getSelectedIndex();
            if (currentId == -1)
                return controller.getPrgStates().get(0);
            else
                return controller.getPrgStates().get(currentId);
        }
    }

    @FXML
    public void changePrg(MouseEvent event) {
        populateExe();
        populateSymTable();
    }

    @FXML // need to put here fxml so that can be connected to the button
    private void makeOneStep() {
        try {
            //ExecutorService executor = Executors.newFixedThreadPool(2);
            List<ProgramState> prgList = controller.getPrgStates();
            //populateIds();
            if(!prgList.isEmpty()){
                //if(!this.getCurrentPrg().getExeStack().isEmpty())
                //{
                    controller.conservativeGarbageCollector(prgList);
                    controller.oneStepForAllPrg(prgList);
                    //this.controller.repo.setPrgList(prgList);
                    populate();
                    prgList = controller.removeCompletedPrg(controller.getPrgStates());
                    controller.repo.setPrgList(prgList);
                    populateIds();
                //}
                //else
                //{
                  //  Alert alert = new Alert(Alert.AlertType.WARNING);
                    //alert.setTitle("Warning");
                   // alert.setContentText("Nothing more to execute in this program state");
                   // alert.showAndWait();
                //}
            }
            else
            {
                Alert alert = new Alert(Alert.AlertType.WARNING);
                alert.setTitle("Warning");
                alert.setContentText("Nothing more to execute");
                alert.showAndWait();
                controller.shutDown();
            }
            //executor.shutdownNow();

        } catch (InterruptedException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error encountered!");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }
}
