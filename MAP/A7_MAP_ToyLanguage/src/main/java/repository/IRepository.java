package repository;

import controller.MyException;
import model.ProgramState;

import java.io.IOException;
import java.util.List;

public interface IRepository {
    //ProgramState getCurrentProgramState();
    void add(ProgramState programState);
    void logPrgStateExec(ProgramState prg) throws MyException, IOException;
    List<ProgramState> getPrgList();
    void setPrgList(List<ProgramState> prgList);
}
