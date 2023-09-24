#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t logind_pid, bash_pid, ps_pid, vim_pid, python_pid, sshd_pid, tcsh_pid;

    // Create logind process
    logind_pid = fork();
    if (logind_pid == 0) {
        // Child process (logind)
        printf("logind (PID %d)\n", getpid());

        // Create bash process
        bash_pid = fork();
        if (bash_pid == 0) {
            // Child process (bash)
            printf("  bash (PID %d)\n", getpid());

            // Create ps process
            ps_pid = fork();
            if (ps_pid == 0) {
                // Child process (ps)
                printf("    ps (PID %d)\n", getpid());
                exit(0);
            } else if (ps_pid < 0) {
                perror("Failed to fork ps");
                exit(1);
            }

            // Create vim process
            vim_pid = fork();
            if (vim_pid == 0) {
                // Child process (vim)
                printf("    vim (PID %d)\n", getpid());
                exit(0);
            } else if (vim_pid < 0) {
                perror("Failed to fork vim");
                exit(1);
            }

            exit(0);
        } else if (bash_pid < 0) {
            perror("Failed to fork bash");
            exit(1);
        }

        // Wait for child processes to complete
        wait(NULL);
        wait(NULL);
        exit(0);
    } else if (logind_pid < 0) {
        perror("Failed to fork logind");
        exit(1);
    }

    // Create python process
    python_pid = fork();
    if (python_pid == 0) {
        // Child process (python)
        printf("python (PID %d)\n", getpid());
        exit(0);
    } else if (python_pid < 0) {
        perror("Failed to fork python");
        exit(1);
    }

    // Create sshd process
    sshd_pid = fork();
    if (sshd_pid == 0) {
        // Child process (sshd)
        printf("sshd (PID %d)\n", getpid());

        // Create tcsh process
        tcsh_pid = fork();
        if (tcsh_pid == 0) {
            // Child process (tcsh)
            printf("  tcsh (PID %d)\n", getpid());
            exit(0);
        } else if (tcsh_pid < 0) {
            perror("Failed to fork tcsh");
            exit(1);
        }

        exit(0);
    } else if (sshd_pid < 0) {
        perror("Failed to fork sshd");
        exit(1);
    }

    // Wait for child processes to complete
    wait(NULL);
    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
