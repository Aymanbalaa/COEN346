package ProgAss;
import java.util.BitSet;

class PidManager {
    private static final int MIN_PID = 300;
    private static final int MAX_PID = 5000;
    public BitSet pidMap;

    public PidManager() {
        int numberOfPids = MAX_PID - MIN_PID + 1;
        pidMap = new BitSet(numberOfPids);
        pidMap.clear(); 
    }

    public int allocateMap() {
        if (pidMap == null) {
            return -1; 
        }
        return 1; 
    }
    

    public int allocatePid() {
        int pid = pidMap.nextClearBit(0);
        if (pid >= 0 && pid <= MAX_PID) {
            pidMap.set(pid);
            return pid + MIN_PID;
        }
        return -1; 
    }

    public void releasePid(int pid) {
        if (pid >= MIN_PID && pid <= MAX_PID) {
            pidMap.clear(pid - MIN_PID);
        }
    }
}
