#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("[ID = %d] I am the root parent\n", getpid());
    // Create child C1
    pid_t pid_C1 = fork();
    if (pid_C1 == 0) {
        printf("[ID = %d] My parent is [%d]\n", getpid(), getppid());

        // Create child C2
        pid_t pid_C2 = fork();
        if (pid_C2 == 0) {   
        printf("[ID = %d] My parent is [%d]\n", getpid(), getppid());
        }
    } else {
        // Create child C3
        pid_t pid_C3 = fork();
        if (pid_C3 == 0) 
            printf("[ID = %d] My parent is [%d]\n", getpid(), getppid());

            // Create child C4
            pid_t pid_C4 = fork();
            if (pid_C4 == 0) {
                printf("[ID = %d] My parent is [%d]\n", getpid(), getppid());
            }
        } 
        else {
            while(wait(NULL) > 0);
        }
    }
    return 0;
}
