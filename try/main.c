#include "minishell.h"

int main() {
    char* input;
    char prompt[] = "Enter command: ";

    // Loop to read and process commands
    while (1) {
        input = readline(prompt); // Display prompt and read user input

        if (!input) {
            // Handle EOF or error
            break;
        }

        // Trim leading and trailing whitespace
        char* trimmed_input = strdup(input);
        char* end = trimmed_input + strlen(trimmed_input) - 1;
        while (end > trimmed_input && *end == ' ') {
            *end-- = '\0';
        }
        while (*trimmed_input && *trimmed_input == ' ') {
            ++trimmed_input;
        }

        if (*trimmed_input) {
            // Add non-empty command to history
            add_history(trimmed_input);
        } else {
            // Free memory if command is empty
            free(trimmed_input);
        }

        // Simulate command processing (replace with actual command execution logic)
        printf("Executing command: %s\n", trimmed_input);

        // Free allocated memory for input
        free(input);
    }

    // Clean up readline resources
    rl_clear_history();
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();

    return 0;
}

/*
void setRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Function to reset terminal to original mode
void resetRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO); // Enable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void    prompt(void)
{
    char    s[1000];
    char    c;
//    char    *p;

    getcwd(s, 1000);
    ft_strlcat(s, "> ", ft_strlen(s) + 3);
    //p = readline(c);
    write(1, s, ft_strlen(s));
    while (1)
    {
        read(1, &c, 1);
        if (c == 27)
        {
            read(1, s, 1);
            //write(1, s, 1);
            if (s[0] == '[')
            {    
                read(1, s + 1, 1);
                if (s[1] == 'A')
                    write(1, "upkey", 5);
                else if (s[1] == 'B')
                    write(1, "downkey", 7);
                //else if (s[1] == 'C' || s[1] == 'D' || s[1] == 'F' || s[1] == 'H')
                else if (s[1] == 'C' || s[1] == 'D')
                {
                    write(1, &c, 1);
                    write(1, s, 2);
                }
                else
                    write(1, s, 2);
            }
            else
                write(1, s, 1);
        }
        else
            write(1, &c, 1);
    }
}

int	main(void)
{
    
    //char    c;
    setRawMode();


    prompt();
    resetRawMode();
}
*/