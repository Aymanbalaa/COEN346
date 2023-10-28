#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    int N1 = atoi(argv[1]);

    // Fork the first child process to compute the sum of positive integers
    pid_t pid_sum = fork();
    if (pid_sum == 0) {
        int sum = 0;
        for (int i = 1; i <= N1; ++i) {
            sum += i;
        }
        printf("[ID = %d] Sum of positive integers up to %d is %d\n", getpid(), N1, sum);
        exit(0);
    }

    // Fork the second child process to compute the factorial
    pid_t pid_fact = fork();
    if (pid_fact == 0) {
        int factorial = 1;
        for (int i = 1; i <= N1; ++i) {
            factorial *= i;
        }
        printf("[ID = %d] Factorial of %d is %d\n", getpid(), N1, factorial);
        exit(0);
    }

    // Parent process waits for both children to finish
    waitpid(pid_sum, NULL, 0);
    waitpid(pid_fact, NULL, 0);

    // Parent process prints the completion message
    printf("[ID = %d] Done\n", getpid());

    return 0;
}
