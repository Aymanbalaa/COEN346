#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void printProcessInfo(int id) {
    printf("[ID = %d] My parent is [%d]\n", getpid(), id);
}

int main() {
    printf("COEN 346 OPERATING SYSTEMS\n");
    printf("[ID = %d] I am the root parent\n", getpid());

    // Create child C1
    pid_t pid_C1 = fork();
    if (pid_C1 == 0) {
        // C1 process
        printProcessInfo(getppid());

        // Create grandchild C2
        pid_t pid_C2 = fork();
        if (pid_C2 == 0) {
            // C2 process
            printProcessInfo(getppid());
        } else {
            // C1 process waits for C2 to finish
            wait(NULL);
        }
    } else {
        // Parent process
        // Create child C3
        pid_t pid_C3 = fork();
        if (pid_C3 == 0) {
            // C3 process
            printProcessInfo(getppid());

            // Create grandchild C4
            pid_t pid_C4 = fork();
            if (pid_C4 == 0) {
                // C4 process
                printProcessInfo(getppid());
            } else {
                // C3 process waits for C4 to finish
                wait(NULL);
            }
        } else {
            // Parent process waits for all child processes to finish
            while(wait(NULL) > 0);
        }
    }

    return 0;
}
