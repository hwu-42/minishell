#include "minishell.h"

int    check_enclosed(char *s)
{
    while(*s != 0 && *s != 39 && *s != 34)
    {
        //printf("%c", *s);
        s++;
    }
    if (*s == 39)
    {
        s++;
        while(*s && *s != 39)
            s++;
        if (*s == 0)
            return (0);
        else
        {
            if (*(s + 1) == 0)
                return (1);
            else
                return(check_enclosed(s + 1));
        }
    }
    else if (*s == 34)
    {
        s++;
        while(*s && *s != 34)
            s++;
        if (*s == 0)
            return (0);
        else
        {
            if (*(s + 1) == 0)
            return (1);
            else
               check_enclosed(s + 1);
        }
    }
    else
        return (1);
}

int main(void)
{
    char    *input;
    char    *temp;


    while (1)
    {
        input = readline("$> ");
        
        while (check_enclosed(input) == 0)
        {
            input = strncat(input, "\n", strlen(input) + 2);
            temp = readline("");
            input = strncat(input, temp, strlen(input) + strlen (temp) + 1);
        }
        //printf("%s\n", input);
        if (input)
            add_history(input);
        printf("%s\n", input);
    }
}
