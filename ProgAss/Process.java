package ProgAss;

public class Process {
    String name;
    int pid;
    public int priority;
    public int cpuBurst;
    public int arrivalTime;
    public int numChildren;

    public Process(String name ,int pid, int priority, int cpuBurst, int arrivalTime, int numChildren) {
        this.name =name;
        this.pid = pid;
        this.priority = priority;
        this.cpuBurst = cpuBurst;
        this.arrivalTime = arrivalTime;
        this.numChildren = numChildren;
    }

    public String getName()
    {
        return name;
    }
    public int getPid() {
        return pid;
    }

    public int getPriority() {
        return priority;
    }

    public int getCpuBurst() {
        return cpuBurst;
    }

    public int getArrivalTime() {
        return arrivalTime;
    }

    public int getNumChildren() {
        return numChildren;
    }

    // You can add more methods and attributes as needed
}
