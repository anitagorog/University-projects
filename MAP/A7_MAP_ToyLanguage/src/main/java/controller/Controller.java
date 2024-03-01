package controller;

import model.stmts.IStmt;
import model.ProgramState;
import model.types.RefType;
import model.utils.IHeapTable;
import model.utils.MyIDictionary;
import model.values.Value;
import repository.IRepository;
import model.utils.MyIStack;
import model.values.RefValue;

import java.io.IOException;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {
    public IRepository repo;
    boolean flag;
    ExecutorService executor = Executors.newFixedThreadPool(2);

    public Controller(IRepository repo) {
        this.repo = repo; flag = true;
    }

    Map<Integer, Value> safeGarbageCollector(List<Integer> symTableAddr, Map<Integer,Value> heap){
        return heap.entrySet().stream()
                .filter(e->symTableAddr.contains(e.getKey()))
                    .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    List<Integer> getAllAddresses(Collection<Value> symTableValues, IHeapTable<Integer, Value> heapTable)
    {
        ConcurrentLinkedDeque<Integer> symTableAdr = symTableValues.stream()
                .filter(v-> v instanceof RefValue)
                .map(v-> {
                    RefValue v1 = (RefValue)v;
                    return v1.getAddr();
                })
                .collect(Collectors.toCollection(ConcurrentLinkedDeque::new));

        // System.out.println("symTable addr: "+symTableAdr);
        symTableAdr.stream()
                .forEach(a-> {
                    Value v= heapTable.getContent().get(a);
                    if (v instanceof RefValue) {
                        if (!symTableAdr.contains(((RefValue) v).getAddr()))
                            symTableAdr.add(((RefValue) v).getAddr());
                        //v = ((RefValue) v).getInner();
                    }
                });
        //System.out.println("symTable + heapTable addr: "+symTableAdr);
        return symTableAdr.stream().toList();
    }

    public void conservativeGarbageCollector(List<ProgramState> programStates) {
        List<Integer> symTableAddresses = programStates.stream()
                        .map(p -> getAllAddresses(p.getSymTable().getContent().values(),
                                p.getHeapTable()))
                        .map(Collection::stream)
                        .reduce(Stream::concat).orElse(null)
                .collect(Collectors.toList());
        programStates.forEach(p -> p.getHeapTable().setContent(
                safeGarbageCollector(symTableAddresses, p.getHeapTable().getContent())));
    }

    public List<ProgramState> removeCompletedPrg(List<ProgramState> inPrgList)
    {
        return inPrgList.stream()
                .filter(p -> p.isNotCompleted())
                .collect(Collectors.toList());
    }

    public void oneStepForAllPrg(List<ProgramState> prgList) throws InterruptedException {
        // before the execution, print the PrgState List into the log file
        prgList.forEach(prg -> {
            try {
                repo.logPrgStateExec(prg);
            } catch (MyException | IOException e) {
                System.out.println(e.getMessage());
            }
        });
        // RUN concurrently one step for each of the existing PrgStates
        // prepare the list of callables
        List<Callable<ProgramState>> callList = prgList.stream()
                .map((ProgramState p) -> (Callable<ProgramState>)(() -> {return p.oneStep();}))
                .collect(Collectors.toList());
        // start the execution of the callables
        // it returns the list of new created PrgStates (namely threads)
        List<ProgramState> newPrgList = executor.invokeAll(callList). stream()
                .map(future -> { try { return future.get();}
                catch(ExecutionException | InterruptedException e) {
                    //here you can treat the possible
                    // exceptions thrown by statements
                    // execution, namely the green part
                    // from previous allStep method
                    System.out.println(e.getMessage());
                    return null;
                }
                })
                .filter(p -> p!=null)
                            .collect(Collectors.toList());
        // add the new created threads to the list of existing threads
        prgList.addAll(newPrgList);
        // after the execution, print the PrgState List into the log file
        prgList.forEach(prg -> {
            try {
                repo.logPrgStateExec(prg);
            } catch (MyException | IOException e) {
                System.out.println(e.getMessage());
            }
        });
        //Save the current programs in the repository
        repo.setPrgList(prgList);
    }

    public void allStep() throws InterruptedException {
        executor = Executors.newFixedThreadPool(2);
        // remove the completed programs
        List<ProgramState> prgList = removeCompletedPrg(repo.getPrgList());
        while(prgList.size() > 0){
            // garbage collector
            /*for (ProgramState prg : prgList) {
                prg.getHeapTable().setContent(safeGarbageCollector(
                        getAllAddresses(prg.getSymTable().getContent().values(), prg.getHeapTable()),
                        prg.getHeapTable().getContent()));
            }*/

            conservativeGarbageCollector(prgList);
            oneStepForAllPrg(prgList);
            // remove the completed programs
            prgList=removeCompletedPrg(repo.getPrgList());
            //conservativeGarbageCollector(prgList);
        }
        executor.shutdownNow();
        // HERE the repository still contains at least one Completed Prg
        // and its List<PrgState> is not empty. Note that oneStepForAllPrg calls the method
        // setPrgList of repository in order to change the repository

        // update the repository state
        repo.setPrgList(prgList);
    }

    public String getNumberOfPrgStates() {
        return String.valueOf(repo.getPrgList().size());
    }

    public List<ProgramState> getPrgStates() {
        return this.repo.getPrgList();
    }

    public void shutDown() {this.executor.shutdownNow();}








    Map<Integer, Value> unsafeGarbageCollector(List<Integer> symTableAddr, Map<Integer,Value> heap){
        return heap.entrySet().stream()
                .filter(e->symTableAddr.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }
    List<Integer> getAddrFromSymTable(Collection<Value> symTableValues){
        return symTableValues.stream()
                .filter(v-> v instanceof RefValue)
                .map(v-> {RefValue v1 = (RefValue)v; return v1.getAddr();})
                .collect(Collectors.toList());
    }

    /*private ProgramState oneStep(ProgramState state) throws MyException {
        MyIStack<IStmt> stk = state.getExeStack();
        if (stk.isEmpty()) throw new MyException("program-state stack is empty");
        IStmt crtStmt = stk.pop();
        return crtStmt.execute(state);
    }*/

    /*public void allStep() throws MyException, IOException {
        ProgramState prg = repo.getPrgList().get(0); // repo is the controller field of type MyRepoInterface
        // here you can display the prg state

        // SAVE IN FILE
        repo.logPrgStateExec(prg);

        if(flag)
            System.out.println(prg);
        while (!prg.getExeStack().isEmpty()) {
            //this.oneStep(prg);
            prg.oneStep();

            // SAVE IN FILE
            repo.logPrgStateExec(prg);

            //prg.getHeapTable().setContent(unsafeGarbageCollector(
              //      getAddrFromSymTable(prg.getSymTable().getContent().values()),
                //    prg.getHeapTable().getContent()));
            prg.getHeapTable().setContent(safeGarbageCollector(
                    getAllAddresses(prg.getSymTable().getContent().values(), prg.getHeapTable()),
                                    prg.getHeapTable().getContent()));
            repo. logPrgStateExec(prg);
            //here you can display the prg state
            if (flag)
               System.out.println(prg);

        }
        if (!flag)
            System.out.println(prg.getOut().toString());
    }*/
}
