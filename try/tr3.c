#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function for SIGINT
void handle_sigint(int sig) {
    printf("Caught SIGINT (Ctrl-C). Hello from the handler!\n");
    // No exit or termination here, so the process continues running
}

int main() {
    // Register the custom signal handler for SIGINT
    signal(SIGINT, handle_sigint);

    // Infinite loop to keep the program running
    while (1) {
        printf("Running... Press Ctrl-C to trigger SIGINT.\n");
        sleep(5); // Sleep for 5 seconds to simulate ongoing work
    }

    return 0;
}
