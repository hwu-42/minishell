#include "minishell.h"

size_t  max(size_t a, size_t b)
{
    if (a > b)
        return a;
    return (b);
}

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

int heap_env(t_d *d)
{
    int i;
    char    **key;
    char    **nvs;

    i = 0;
    key = *(d->env);
    while (*key)
    {
        i++;
        key++;
    }
    nvs = malloc(sizeof(char *) * (i + 1));
    if (nvs == NULL)
        return (0);
    nvs[i] = NULL;
    key = *(d->env);
    *(d->env) = nvs;
    while (*key)
        *nvs++ = ft_strdup(*key++);
    return (1);
}

static void	print_list(t_list *head)
{
	t_list	*current;

	if (head == NULL)
        return ;
    current = head;
	while (current != NULL) {
		printf("Token: %s, Type: %d\n", current->token, current->type);
		current = current->next;
	}
}

int main(int argc, char **argv, char **envp)
{
    char    *input;
    t_d     data;
//    char    *temp = NULL;
//    char    **args;
//    char    *eof;
    t_list *head = NULL;

    if (argc > 0)
        argv[0] = argv[0];
    data.env = &envp;
    if(!heap_env(&data))
        exit(1);
    prt_env(&data); //debug
    while (1)
    {
        data.s = readline("new env to edd:\n");
        if (*(data.s) == 0)
            break;
        export_env(&data);
    }
    while (1)
    {
        data.s = readline("env to unset:\n");
        if (*(data.s) == 0)
            break;
        unset_env(&data);
    }
    printf("main: will call get command\n");//debug
    input = get_command();
//    printf("main(): received command is:\n");//debug
//    printf("%s\n", input);//debug
    printf("main(): strip the command\n");//debug
    data.s = strimmed(input);

//    printf("main(): trimmed command is: %s\n", data.s);//debug
    while (dif_str(data.s, "exit"))
    {
        printf("main(): start tokenization\n");//debug
        tokenize_and_classify(data.s, &head);
        printf("main(): tokenization done\n");//debug
        print_list(head);
        free_list(head);
        head = NULL;
        if (input)
            free (input);
        input = get_command();
        printf("main(): received command\n");//debug
        data.s = strimmed(input);
        printf("main(): strip done\n");//debug
/*        if (!ft_strncmp(strimmed(input), "echo", 4) && white_space(strimmed(input)[4]))
        {
            my_echo(&data);
        }
        else if (!ft_strncmp(strimmed(input), "pwd", 3) && (white_space(strimmed(input)[3]) || strimmed(input)[3] == 0))
            my_pwd(&data);
        else if (!ft_strncmp(strimmed(input), "cd", 2) && white_space(strimmed(input)[2]))
            my_cd(&data);
        else if (!ft_strncmp(strimmed(input), "env", 3) && (white_space(strimmed(input)[3]) || strimmed(input)[3] == 0))
            prt_env(&data);
        if (*strimmed(input))
            add_history(strimmed(input));
        //printf("%s\n", input);
        free (input);
        input = get_command();
        printf("main(): received command is: %s\n", input);//debug
        data.s = strimmed(input);
        printf("main(): trimmed command is: %s\n", input);//debug*/
    }
    exit (0);
}