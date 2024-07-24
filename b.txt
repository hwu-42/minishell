#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

// Global variable to store the exit status of the last executed command
int last_exit_status = 0;

// Function to execute a command
void execute_command(char *command) {
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) {
        // Child process
        execlp(command, command, NULL);
        // If execlp fails
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            last_exit_status = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            last_exit_status = 128 + WTERMSIG(status);
        }
    }
}

// Function to handle the '$?' expansion
void expand_dollar_question(char *input) {
    char buffer[MAX_INPUT_SIZE];
    char *pos = input;
    char *write_pos = buffer;

    while (*pos) {
        if (pos[0] == '$' && pos[1] == '?') {
            snprintf(write_pos, MAX_INPUT_SIZE - (write_pos - buffer), "%d", last_exit_status);
            write_pos += strlen(write_pos);
            pos += 2;
        } else {
            *write_pos++ = *pos++;
        }
    }
    
    *write_pos = '\0';
    strcpy(input, buffer);
}

// Main loop of the shell
int main() {
    char input[MAX_INPUT_SIZE];

    while (1) {
        printf("minishell> ");
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        // Remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Handle '$?' expansion
        expand_dollar_question(input);

        // Execute command
        if (strlen(input) > 0) {
            execute_command(input);
        }
    }

    return 0;
}
