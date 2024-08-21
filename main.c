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
            printf("unclose_eofs(): no unclosed eof anymore!!\n");//debug
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
    while (end >= s && white_space(*end))
    {
        *end-- = '\0';
    }
    while (white_space(*s))
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
        signal(SIGQUIT, SIG_DFL);
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

/* //debug
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
*/

void    free_in(t_c *cmd)
{
    t_c *temp;

    temp = cmd->in;
    while (temp)
    {
        mfree(temp->ifile);
        cmd->in = NULL;
        cmd = temp;
        temp = temp->in;
        mfree(cmd);
    }
}

void    free_out(t_c *cmd)
{
    t_c *temp;

    temp = cmd->out;
    while (temp)
    {
        mfree(temp->ofile);
        cmd->out = NULL;
        cmd = temp;
        temp = temp->out;
        mfree(cmd);
    }
}

void    free_command_list(t_c *cmd)
{
    t_c *temp;
    char    **s;

    while (cmd)
    {
        //printf("free_command_line(): now to free one command node\n");//debug
        if (cmd->in)
            free_in(cmd);
        if (cmd->out)
            free_out(cmd);
        if (cmd->tp < 2)
        {
            s = cmd->cmd;
            while (*s)
            {
                mfree(*s);
                s++;
            }
            mfree (s);
        }
        temp = cmd->next;
        mfree(cmd);
        cmd = temp;
        //printf("free_command_line(): free one command node done!!!\n");//debug
    }

}

void    signal_handle(int sig)
{
    if (sig == SIGINT)
    {
        rl_replace_line("", 0);
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_redisplay();
    }
}


int main(int argc, char **argv, char **envp)
{
    char    *input;
    t_d     data;
    t_list  *tokens;
    t_c     *cmd;

    signal(SIGINT, signal_handle);
    signal(SIGQUIT, SIG_IGN);
    if (argc > 0)
        argv[0] = argv[0];
    data.env = &envp;
    if(!heap_env(&data))
        exit(1);
    //prt_env(&data); //debug

    printf("main: will call get command\n");//debug
    input = get_command();
//    printf("main(): received command is:\n");//debug
//    printf("%s\n", input);//debug
 //   printf("main(): strip the command\n");//debug

//    printf("main(): trimmed command is: %s\n", data.s);//debug
    while (dif_str(strimmed(input), "exit"))
    {
        data.s = strimmed(input);
        printf("main(): trimmed command is:----------------\n%s\n", data.s);//debug
        if (data.s)
            add_history(data.s);
        //printf("%s\n", input);
        tokens = tokenize_input(data.s);
        printf("main(): tokens list is:----------------\n");//debug
        print_token_list(tokens);
        cmd =load_token_into_cmd(tokens);
        if (cmd)
        {
           // printf("main(): i'm a separator****in command structure:\n"); //debug
            //print_cmd_list(cmd); debug
            convert_arg_2_string(cmd, &data);
          //  printf("main(): i'm a separator****after expansion, cmd is:\n"); //debug
          //  print_cmd_list(cmd);
           // printf("main(): i'm a separator******execute cmd:\n"); //debug
            execute_command_line(cmd, &data);
            //printf("main(): now to free command line\n");//debug
            free_command_list(cmd);
        }
        //printf("main(): now to free input buffer line\n");//debug
        mfree(input);
        input = get_command();
        if (input == NULL) {
            // ctrl-D: exit the shell
            exit(0);
        }
        printf("main(): received command is: %s\n", input);//debug
    }
    exit (0);
}
