#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3, pid4, pid5, pid6;
    //parent process
    printf("systemd\n");

    pid1 = fork();
    if (pid1 == 0) {
        printf("|--logind\n");
    
        pid2 = fork();
        if (pid2 == 0) {
            printf("   |--bash\n");
            
            pid3 = fork();
            if (pid3 == 0) {
                printf("      |--ps\n");
                return 0;
            }
            wait(NULL);
            printf("      |--vim\n");
            return 0;
        }
        wait(NULL);
        return 0;
    } else {
        wait(NULL);

        
        pid4 = fork();
        if (pid4 == 0) {
            printf("|--python\n");
            return 0;
        } else {
            wait(NULL);

            
            pid5 = fork();
            if (pid5 == 0) {
                printf("|--sshd\n");

                
                pid6 = fork();
                if (pid6 == 0) {
                    printf("   |--sshd\n");
                    return 0;
                }
                wait(NULL);
                printf("   |--tcsh\n");
                return 0;
            }
        }
    }

    wait(NULL);
    return 0;
}
