package repository;

import controller.MyException;
import model.ProgramState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;


public class Repository implements IRepository{

    String logFilePath; // from keyboard using Scanner
    List<ProgramState> programStateList;

    public Repository(String logF) {
        programStateList = new ArrayList<>();
        logFilePath = logF;
    }

    public Repository(ProgramState prg, String logF) {
        programStateList = new ArrayList<>();
        programStateList.add(prg);
        logFilePath = logF;
    }

    /*@Override
    public ProgramState getCurrentProgramState() {
        try {
            return programStateList.get(0);
        } catch (IndexOutOfBoundsException indexOutOfBoundsException) {
            return null;
        }
    }*/

    @Override
    public String toString() {
        return "Repository{" +
                "programStateList=" + programStateList +
                '}';
    }

    @Override
    public void add(ProgramState programState) {
        programStateList.add(programState);
    }

    @Override
    public void logPrgStateExec(ProgramState prg) throws MyException, IOException {
        // this.getCurrentProgramState().addToFileTable(this.logFilePath); !!!!!!!!!!!!!!!!!!!!!!!!!!!!
        PrintWriter logFile= new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
        logFile.write(prg.toString());
        logFile.close();
    }

    @Override
    public List<ProgramState> getPrgList() {
        return this.programStateList;
    }

    @Override
    public void setPrgList(List<ProgramState> prgList) {
        this.programStateList = prgList;
    }
}
