#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void sigint_handler(int sig) {
    printf("Process %d received SIGINT\n", getpid());
}

int main() {
    signal(SIGINT, sigint_handler);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process %d waiting for SIGINT\n", getpid());
        while (1) {
            // Infinite loop to keep the child process running
        }
    } else {
        // Parent process
        printf("Parent process %d waiting for SIGINT\n", getpid());
        wait(NULL); // Wait for child process to terminate
    }

    return 0;
}
