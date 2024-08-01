#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function declarations
void execute_command(char *line);
void execute_echo(char *args[]);
void execute_cd(char *path);
void execute_pwd();
void execute_export(char *args[]);
void execute_unset(char *args[]);
void execute_env();
void execute_exit();

// Main function
int main() {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        printf("minishell> ");
        getline(&line, &len, stdin);

        // Remove newline character from the end
        line[strcspn(line, "\n")] = 0;

        // Execute the command
        execute_command(line);
    }

    free(line);
    return 0;
}

// Function to execute the command
void execute_command(char *line) {
    char *args[100];
    char *token = strtok(line, " ");
    int i = 0;

    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[0] == NULL) {
        return;
    }

    if (strcmp(args[0], "echo") == 0) {
        execute_echo(args);
    } else if (strcmp(args[0], "cd") == 0) {
        execute_cd(args[1]);
    } else if (strcmp(args[0], "pwd") == 0) {
        execute_pwd();
    } else if (strcmp(args[0], "export") == 0) {
        execute_export(args);
    } else if (strcmp(args[0], "unset") == 0) {
        execute_unset(args);
    } else if (strcmp(args[0], "env") == 0) {
        execute_env();
    } else if (strcmp(args[0], "exit") == 0) {
        execute_exit();
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("exec");
            exit(EXIT_FAILURE);
        } else {
            wait(NULL);
        }
    }
}

// Built-in command implementations

void execute_echo(char *args[]) {
    int i = 1;
    int newline = 1;

    if (args[1] != NULL && strcmp(args[1], "-n") == 0) {
        newline = 0;
        i = 2;
    }

    while (args[i] != NULL) {
        printf("%s", args[i]);
        if (args[i + 1] != NULL) {
            printf(" ");
        }
        i++;
    }

    if (newline) {
        printf("\n");
    }
}

void execute_cd(char *path) {
    if (path == NULL) {
        char *home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "cd: HOME not set\n");
        } else if (chdir(home) != 0) {
            perror("cd");
        }
    } else if (chdir(path) != 0) {
        perror("cd");
    }
}

void execute_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("pwd");
    }
}

void execute_export(char *args[]) {
    if (args[1] == NULL) {
        fprintf(stderr, "export: missing operand\n");
    } else {
        for (int i = 1; args[i] != NULL; i++) {
            putenv(args[i]);
        }
    }
}

void execute_unset(char *args[]) {
    if (args[1] == NULL) {
        fprintf(stderr, "unset: missing operand\n");
    } else {
        for (int i = 1; args[i] != NULL; i++) {
            unsetenv(args[i]);
        }
    }
}

void execute_env() {
    extern char **environ;
    for (char **env = environ; *env != 0; env++) {
        printf("%s\n", *env);
    }
}

void execute_exit() {
    exit(0);
}
