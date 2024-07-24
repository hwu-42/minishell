#include "minishell.h"

size_t  max(size_t a, size_t b)
{
    if (a > b)
        return a;
    return (b);
}

/*
//enhanced ver
//return 1 for enclosed, 0 for unenclosed
int    check_enclosed(char *s, char **eof)
{
    while(*s != 0 && *s != 39 && *s != 34 && *s != '<')
        s++;
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
               return(check_enclosed(s + 1));
        }
    }
    else if (*s == '<' && *(s + 1) == '<')
        return (check_here_doc(s));
    else
        return (1);
}*/

//tbc to release memory
int clean_exit(void)
{
    printf("clean_exit, please complete this function ERROR\n");
    return (0);
}


//add = 1 for add, -1 for remove first, 0 for check first,
//return 
char    *unclosed_eofs(int add, char *eof)
{
    static  char    *eofs[MAXMM];
    int             i;
    char            *temp;

    if (add == 1)
    {
        i = 0;
        while (i < MAXMM)
        {
            if (eofs[i])
                i++;
            else
                break;
        }
        if (i == MAXMM)
        {
            printf("two many unclosed syntex\n");
            return (NULL);
        }
        else
        {
            eofs[i] = eof;
            return (eof);
        }
    }
    else if (add == -1)
    {
        i = 0;
        while (i < MAXMM)
        {
            if (eofs[i] == NULL)
                i++;
            else
                break;
        }
        if (i == MAXMM)
        {
            printf("unclose_eofs(): given eof not found, check your program!!\n");//debug
            return (NULL);
        }
        else
        {
            printf("unclose_eofs(): eof:%s is removed\n", eofs[i]);//debug
            temp = eofs[i];
            eofs[i] = NULL;
            return (temp);
        }
    }
    else
    {
        i = 0;
        while (i < MAXMM)
        {
            if (eofs[i] == NULL)
                i++;
            else
                break;
        }
        if (i == MAXMM)
            return (NULL);
        else
            return (eofs[i]);
    }
}

void    printsini(char *s) //for debug
{
    size_t i;

    i = 0;
    while (i <= strlen(s))
        printf("%d, ", s[i++]);
}

char    *strimmed(char *s)
{
    char    *end;
    
    if (s == NULL)
        return (NULL);
    if (*s == 0)
        return (s);
    end = s + ft_strlen(s) - 1;
    while (end >= s && *end == ' ')
    {
        *end-- = '\0';
    }
    while (*s == ' ')
    {
        s++;
    }
    return (s);
}

void    parse_command(char **args)
{
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return;
    } else if (pid == 0) {
        // Child process
        execve(args[0], args, NULL);
        perror("execve"); // execve returns only on error
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process terminated by signal %d\n", WTERMSIG(status));
        }
    }
}

int dif_str(char *s, char *t)
{
    if (s == NULL && t == NULL)
        return (0);
    if (s == NULL || t == NULL)
        return (1);
    else
    {
        while (*s == *t && *s != 0)
        {
            s++;
            t++;
        }
        if (*s == *t)
            return (0);
        return (1);
    }
}

int main(int argc, char **argv, char **envp)
{
    char    *input;
//    char    *temp = NULL;
//    char    **args;
//    char    *eof;

    if (argc > 0)
        argv[0] = argv[0];
    printf("%s\n", *(envp++));
    printf("main: will call get command\n");//debug
    input = get_command();
    while (strcmp(strimmed(input), "exit"))
    {
        if (*strimmed(input))
            add_history(strimmed(input));
            /*
        printsini(input);//debug
        printf("\n");//debug
        printsini(strimmed(input));//debug
        */
        printf("%s\n", input);
        free (input);
        input = get_command();
    }
    exit (0);
}
