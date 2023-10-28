package ProgAss;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        PidManager pidManager = new PidManager();
        int result = pidManager.allocateMap();

        if (result == -1) {
            System.out.println("Error: Unable to initialize PID Manager.");
            return;
        }

        List<Process> processes = new ArrayList<>();

        // Read processes from the file and assign PIDs using pidManager.allocatePid()
        String filePath = "ProgAss/Schedule.txt"; // Replace with the actual file path
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            String line;
            int pidCounter = 0;
            while ((line = br.readLine()) != null) {
                String[] tokens = line.split(", ");
                String name =tokens[0];
                int priority = Integer.parseInt(tokens[1]);
                int cpuBurst = Integer.parseInt(tokens[2]);
                int arrivalTime = Integer.parseInt(tokens[3]);
                int numChildren = Integer.parseInt(tokens[4]);

                // Allocate PIDs for the process and its children
                int pid = pidManager.allocatePid();
                if (pid == -1) {
                    System.out.println("Error: Unable to allocate PID for the process.");
                    return;
                }

                Process process = new Process(name,pid,priority, cpuBurst, arrivalTime, numChildren);
                processes.add(process);
                pidCounter++;

                // Allocate PIDs for child processes
                for (int i = 0; i < numChildren; i++) {
                    int childPid = pidManager.allocatePid();
                    if (childPid == -1) {
                        System.out.println("Error: Unable to allocate PID for the child process.");
                        return;
                    }

                    Process childProcess = new Process(name,childPid, priority, cpuBurst, arrivalTime, 0);
                    //processes.add(childProcess);
                    pidCounter++;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        String Decision = "RR";
        int timeQuantum = 4;

        if ( Decision == "FCFS" )
        {
        FCFS fcfs = new FCFS(processes);
        fcfs.schedule();
        }
        else if ( Decision == "RR")
        {
            RR rr = new RR(processes,timeQuantum);
            rr.schedule();
        }
        else if ( Decision == "PRIRR")
        {
            PRIRR prirr = new PRIRR(processes, timeQuantum);
            prirr.schedule();
        }

        

        // Release PIDs after all processes are completed
        for (int i = 0; i < processes.size(); i++) {
            pidManager.releasePid(processes.get(i).pid);
        }
    }
}
