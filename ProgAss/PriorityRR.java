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
        // Output processes
        System.out.println("Priority Round Robin Scheduling Details:");
        System.out.println();
        int currentTime = 0;
        float totalTurnAroundTime = 0;
        float totalWaitingTime = 0;

        // Sort processes by priority in descending order
        PriorityQueue<Process> processQueue = new PriorityQueue<>(Comparator.comparing(Process::getPriority).reversed());
        processQueue.addAll(processes);

        while (!processQueue.isEmpty()) {
            Process process = processQueue.poll();

            System.out.println("Time " + currentTime + ": Process " + process.name +
                    " (PID: " + process.pid + ") created. Arrival Time: " + process.arrivalTime +
                    ", CPU Burst: " + process.cpuBurst);

            int executionTime = Math.min(process.cpuBurst, timeQuantum);
            int completionTime = currentTime + executionTime;
            totalTurnAroundTime += (completionTime - process.arrivalTime);
            totalWaitingTime += (completionTime - process.arrivalTime - executionTime);

            if (executionTime < process.cpuBurst) {
                // The process has remaining CPU burst, add it back to the queue
                process.cpuBurst -= executionTime;
                processQueue.add(process);
            } else {
                System.out.println("Time " + completionTime + ": Process " + process.name +
                        " (PID: " + process.pid + ") deleted");
            }

            currentTime = completionTime;
        }

        // Calculate and print average turnaround time and waiting time
        float averageTurnAroundTime = totalTurnAroundTime / processes.size();
        float averageWaitingTime = totalWaitingTime / processes.size();
        System.out.println("Average Turnaround Time: " + averageTurnAroundTime);
        System.out.println("Average Waiting Time: " + averageWaitingTime);
    }
}
