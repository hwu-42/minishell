#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>

int main(void)
{
    int i = 1;
    char *input;
    
    input = readline("");
    while (input)
    {
        //printf("%s\n", input);
        free (input);
        input = readline("");
    }
    return (0);
}