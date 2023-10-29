package ProgAss;

import java.util.List;

class FCFS extends Scheduler {
    public FCFS(List<Process> processes) {
        super(processes);
    }

    @Override
    void schedule() {

        
        System.out.println("FCFS Scheduling Details:");
        System.out.println();
        int currentTime = 0;
        float totalTurnAroundTime = 0;
        float totalWaitingTime = 0;

        for (Process process : processes) {
            System.out.println("Time " + currentTime + ": Process " + process.name +
                    " (PID: " + process.pid + ") created. Arrival Time: " + process.arrivalTime +
                    ", CPU Burst: " + process.cpuBurst);

            int waitingTime = Math.max(0, currentTime - process.arrivalTime);
            totalWaitingTime += waitingTime;

            // Calculate completion time and turnaround time
            int completionTime = currentTime + process.cpuBurst;
            totalTurnAroundTime += (completionTime - process.arrivalTime);

            System.out.println("Time " + completionTime + ": Process " + process.name +
                    " (PID: " + process.pid + ") deleted");

            currentTime = completionTime;
        }

        // Calculate and print average turnaround time and waiting time
        float averageTurnAroundTime = totalTurnAroundTime / processes.size();
        float averageWaitingTime = totalWaitingTime / processes.size();
        System.out.println("Average Turnaround Time: " + averageTurnAroundTime);
        System.out.println("Average Waiting Time: " + averageWaitingTime);
    }
}
