package ProgAss;
import java.util.*;

class PRIRR extends Scheduler {
    private final int timeQuantum;

    public PRIRR(List<Process> processes, int timeQuantum) {
        super(processes);
        this.timeQuantum = timeQuantum;
    }

    @Override
    void schedule() {
        System.out.println("Priority Round Robin Scheduling Details:");
        System.out.println();
        int currentTime = 0;
        float totalTurnAroundTime = 0;
        float totalBurstTime = 0;
        int completedProcesses = 0;

        // Priorityqueue because we need to use their priorities for scheduling 
        PriorityQueue<Process> processQueue = new PriorityQueue<>(Comparator.comparing(Process::getPriority));

        while (!processes.isEmpty() || !processQueue.isEmpty()) {
            // Add all processes that have arrived to the queue
            for (int i = 0; i < processes.size(); i++) {
                Process process = processes.get(i);
                if (process.arrivalTime <= currentTime) {
                    processQueue.add(process);
                    processes.remove(i);
                    i--;
                }
            }

            if (!processQueue.isEmpty()) {
                Process process = processQueue.poll();

                if (process.cpuBurst == process.originalBurst) {
                    System.out.println("Time " + currentTime + ": Process " + process.name +
                            " (PID: " + process.pid + ") created. Arrival Time: " + process.arrivalTime +
                            ", CPU Burst: " + process.cpuBurst);
                    totalBurstTime += process.originalBurst;
                } else {
                    System.out.println("Time " + currentTime + ": Process " + process.name +
                            " (PID: " + process.pid + ") resumed. Remaining CPU Burst: " + process.cpuBurst);
                }

                int executionTime = Math.min(process.cpuBurst, timeQuantum);
                int completionTime = currentTime + executionTime;

                if (executionTime >= process.cpuBurst) {
                    System.out.println("Time " + completionTime + ": Process " + process.name +
                            " (PID: " + process.pid + ") deleted");
                    totalTurnAroundTime += (completionTime - process.arrivalTime);
                    completedProcesses++;
                }

                currentTime = completionTime;
                
                // add new arrived processes to queue
                for (int i = 0; i < processes.size(); i++) {
                    Process newProcess = processes.get(i);
                    if (newProcess.arrivalTime <= currentTime) {
                        processQueue.add(newProcess);
                        processes.remove(i);
                        i--;
                    }
                }

                if (executionTime < process.cpuBurst) {
                    // NOT DONE ?
                    process.cpuBurst -= executionTime;
                    System.out.println("Time " + currentTime + ": Process " + process.name +
                            " (PID: " + process.pid + ") is waiting.");
                    // Add the unfinished process to the BACKKK of the queue
                    processQueue.add(process);
                }
            } else {
                currentTime++;
            }
        }

        if (completedProcesses > 0) {
            float averageTurnAroundTime = totalTurnAroundTime / completedProcesses;
            float averageBurstTime = totalBurstTime / completedProcesses;
            float averageWaitingTime = averageTurnAroundTime - averageBurstTime;
            System.out.println("Average Turnaround Time: " + averageTurnAroundTime);
            System.out.println("Average Waiting Time: " + averageWaitingTime);
        } else {
            System.out.println("No processes were completed.");
        }
    }
}
