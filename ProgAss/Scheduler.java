package ProgAss;

import java.util.*;

abstract class Scheduler {
    List<Process> processes;

    public Scheduler(List<Process> processes) {
        this.processes = processes;
    }

    abstract void schedule();
   
}

