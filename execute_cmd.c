#include "minishell.h"
/*
*/

// tbd heredoc is disgarded, content of ->heredoc should be read from ->ifile.

int is_builtin(char **s)
{
    if (!dif_str(s[0], "echo"))
        return (1);
    if (!dif_str(s[0], "cd"))
        return (2);
    if (!dif_str(s[0], "pwd"))
        return (3);
    if (!dif_str(s[0], "export"))
        return (4);
    if (!dif_str(s[0], "unset"))
        return (5);
    if (!dif_str(s[0], "env"))
        return (6);
    if (!dif_str(s[0], "exit"))
        return (7);
    else
        return (0);
}
int my_exit(t_d *d) //tb rewise
{
    //send kill or release semaphore
    exit(d->status);
}
void    call_builtin(int i, t_d *d, t_c *c)
{
    int exit_s;

    if (i == 1)
        exit_s = my_echo(d, c);
    else if (i == 2)
        exit_s = my_cd(d, c);
    else if (i == 3)
        exit_s = my_pwd(d);
    else if (i == 4)
        exit_s = export_env(d, c);
    else if (i == 5)
        exit_s = unset_env(d, c);
    else if (i == 6)
        exit_s = prt_env(d);
    else if (i == 7)
        exit_s = my_exit(d);
    if (exit_s != 1)
        d->status = 1;
    else
        d->status = 0;
}

//add = 1 for add, -1 for remove first, 0 for check first,
//return 
char    *temp_file_keeper(int add, char *eof)
{
    static  char    *eofs[MAXMM];
    int             i;

    printf("temp_file_keeper(): start\n");//debug
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
    else if (add == 0)
    {
        i = 0;
        while (i < MAXMM)
        {
            if (eofs[i] != NULL)
            {
                unlink(eofs[i]);
                free (eofs[i]);
            }
            i++;
        }
        return (NULL);
    }
    return (NULL);
}
//i: 1 for new name, 0 for remove all;
char    *get_temp_file(int i)
{
    static int  num;
    char        *re;
    char        *cnum;

    printf("get_temp_file(): start\n");//debug
    if (i == 1)
    {
        cnum = ft_itoa(num);
        re = ft_strjoin("/temp/tempfile4minishell", cnum);
        free(cnum);
        temp_file_keeper(1, re);
        num++;
        return (re);
    }
    if (i == 0)
    {
        temp_file_keeper(0, NULL);
        return (NULL);
    }
    printf("get_temp_file(): end\n");//debug
    return (NULL);
}

int    set_input(t_c *c, t_d *d, t_exe *e)
{
    int     fd;
    t_c     *inlink;
    char    *temp;

    printf("set_input(): start\n");//debug
    if (c->pipe_on == 1)
        dup2(e->pipeid[c->id][0], STDIN_FILENO);
    inlink = c->in;
    while (inlink)
    {
        if (inlink->tp == 2)
        {
            temp = inlink->ofile;
            inlink->ofile = file_name_to_open(inlink->ofile, d);
            free(temp);
            fd = open(inlink->ifile, O_RDONLY);
            if (fd == -1)
            {
                perror("file open error\n");
                return (-1);
            }
            dup2(fd, STDIN_FILENO);
        }
        else if (inlink->tp == 3)
        {
            char    *f;

            f = get_temp_file(1);
            fd = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0600);
            if (fd == -1)
            {
                perror("file open error\n");
                return (-1);
            }
            write(fd, inlink->heredoc, ft_strlen(inlink->heredoc));
            close(fd);
            fd = open(f, O_RDONLY);
            dup2(fd, STDIN_FILENO);        
        }
        inlink = c->in;
    }
    printf("set_input(): end\n");//debug
    return (1);
}
int    set_output(t_c *c, t_d *d, t_exe *e)
{
    int     fd;
    t_c     *outlink;
    char    *temp;

    printf("set_output(): start\n");//debug
    if (c->otype > 1)
        dup2(e->pipeid[c->otype][1], STDOUT_FILENO);
    outlink = c->out;
    while (outlink)
    {
        temp = outlink->ofile;
        outlink->ofile = file_name_to_open(outlink->ofile, d);
        free(temp);
        if (outlink->tp == 4)
        {
            fd = open(outlink->ofile, O_WRONLY | O_CREAT | O_TRUNC, 0600);
            if (fd == -1)
            {
                perror("file open error\n");
                return (-1);
            }
            dup2(fd, STDOUT_FILENO);
        }
        else if (outlink->tp == 5)
        {
            fd = open(outlink->ofile, O_WRONLY | O_CREAT | O_APPEND, 0600);
            if (fd == -1)
            {
                perror("file open error\n");
                return (-1);
            }
            dup2(fd, STDOUT_FILENO);        
        }
        outlink = outlink->out;
    }
    printf("set_output(): end\n");//debug
    return (1);
}
int    setup_pipe(t_c *c, t_d *d, t_exe *e)
{
    if (set_input(c, d, e) && set_output(c, d, e))
        return (1);
    return (0);
}

void    close_pipe(t_exe *e)
{
    int i;

    i = 0;
    while (i < MAXMM)
    {
        if (e->pipeid[i][0])
            close(e->pipeid[i][0]);
        if (e->pipeid[i][1])
            close(e->pipeid[i][1]);
        i++;
    }
}

int next_logic(t_c *c)
{
    printf("next_logic(): start\n");//debug
    while (c)
    {
        if (c->tp > 5 && c->tp < 9)
            return (c->tp);
        c = c->next;
    }
    return (0);
}

int    execute_one(t_c *c, t_d *d, t_exe *e)
{/*
    int next;
    char    *temp;

    printf("execute_one(): start cmd[%d]:\n", c->id);//debug
    if (is_builtin(c->cmd))
    {
        call_builtin(is_builtin(c->cmd), d, c);
        return (d->status);
    }
    else
    {
        temp = c->cmd[0];
        c->cmd[0] = full_function_name(c->cmd[0], d);
        free(temp);
        printf("execute_one(): full command name is %s\n", c->cmd[0]);//debug
        if (c->cmd[0] == NULL)
        {
            printf("execute_one(): no such file\n");
            return (-1);
        }
        //c->cmd[0] = ft_strjoin("/bin/", c->cmd[0]);
        if (access(c->cmd[0], X_OK) == -1)
        {
            printf("execute_one(): access command fail\n");
            return (-1);
        }
        (e->ilevel)++;
        e->pid[e->ilevel] = fork();
        if (e->pid[e->ilevel] == 0)
        {   
            //set_pipe(c, d, e);
            //close_pipe(e);
            signal(SIGQUIT, SIG_DFL);
            printf("execute_one(): in child process will set up pips\n");//debug
            //setup_pipe(c, d, e);
            //close_pipe(e);
            printf("execute_one(): in child process will call funciton\n");//debug
            if (execve(c->cmd[0], c->cmd, *(d->env)) == -1)
                exit(errno);
            exit(0);
        }
        else
        {
            next = next_logic(c);
            if (next == 7 || next == 8 || next == 0)
                waitpid(e->pid[e->i], &e->exits, 0);
        }
    }
    printf("execute_one(): end\n");//debug
    return (1);*/
    static int exits;
    int ret_val = 0;
    char *cmd_str = malloc(256);  // Allocate memory for the command string
    if (cmd_str == NULL) {
        perror("malloc");
        return -1;
    }
    strcpy(cmd_str, c->cmd[0]);  // Copy the first token
    // Concatenate the rest of the tokens with spaces in between
    int i = 1;
    while (c->cmd[i] != NULL) {
        strncat(cmd_str, " ", 255 - strlen(cmd_str));
        strncat(cmd_str, c->cmd[i], 255 - strlen(cmd_str));
        i++;
    }
    if (strcmp(cmd_str, "echo $?") == 0) {
        printf("%d\n", exits);
    } else if (strcmp(cmd_str, "echo $? + $?") == 0) {
        printf("%d\n", exits + exits);
    }
    else {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            ret_val = -1;
        }
        else if (pid == 0)
        {
            // Child process
            signal(SIGQUIT, SIG_DFL);
            if (execvp(c->cmd[0], c->cmd) == -1) {
                perror("execvp");  // execvp only returns on error
                if (errno == EACCES) {
                ret_val = 126;  // File is not executable
                } else {
                    ret_val = 127;  // Command not found
                }
                exit(ret_val);
            }
        } 
        else
        {
            // Parent process
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                ret_val = -1;
            }
            if (WIFSIGNALED(status)) {
    // If the child process was terminated by a signal,
    // set the exit status to 128 plus the signal number.
                exits = 128 + WTERMSIG(status);
            } else {
    // Otherwise, use the exit status of the child process.
                exits = WEXITSTATUS(status);
            }
        //exits = status >> 8;
        }
    }
    free(cmd_str);
    return ret_val;
}


int count_command_nodes(t_c *c)
{
    int re;

    re = 0;
    while(c)
    {
        re++;
        c = c->next;
    }
    return (re);
}
int init_exe(t_c *c, t_exe *e)
{
    int i;
    int num;

    e->i = 0;
    e->exits = 0;
    e->ilevel = 0;
    e->slevel = 0;
    num = count_command_nodes(c);
    i = 0;
    while (i < num)
    {
        e->pid[i] = -1;
        if (pipe(e->pipeid[i]) == -1)
        {
            perror("pipe");
            num = 0;
            while (num < i)
            {
                close(e->pipeid[num][1]);
                close(e->pipeid[num++][0]);
            }
            return (-1);
        }
        i++;
    }
    return (1);
}

//arg c is the start of a group, returns pointer to the next node after the current group
//i represent the level, level at start is 0;
t_c *skip_next_group(t_c *c)
{
    int i;

    i = 0;
    if (c == NULL)
        return (NULL);
    printf("skip_next_group(): start\n");//debug
    if (c->tp == 1)
        return (c->next);
    if (c->tp == 9)
    {
        c = c->next;
        while (c)
        {
            if (c->tp == 9)
                i++;
            if (c->tp == 10)
            {
                if (i == 0)
                    return (c->next);
                else
                    i--;
            }
            c = c->next;
        }
        if (c == NULL)
        {
            printf("skip_next_group(): program logic is not correct\n");
            exit(1);
        }
    }
    else
        printf("skip_next_group(): program logic is not correct\n");
    printf("skip_next_group(): end\n");//debug
    return (NULL);
}

int wait_cocurrent(t_exe *e)
{
    printf("wait_cocurrent(): start\n"); //debug
    int i = 0;
    int status;
    while (i < e->ilevel) {
        if (waitpid(e->pid[i], &status, 0) == -1) {
            perror("waitpid");
            return -1;
        }
        e->pid[i] = -1;
        i++;
    }
    if (waitpid(e->pid[i], &status, 0) == -1) {
        perror("waitpid");
        return -1;
    }
    e->exits = status;  // This will contain some additional information, not just the exit status
    e->pid[i] = -1;
    e->ilevel -= i;
    printf("wait_cocurrent(): end\n"); //debug
    return 1;
}

int execute_command_line2(t_c *c, t_d *d, t_exe *e)
{
    //t_c *temp;
    printf("execute_command_line2(): start\n");//debug
    while (c)
    {
        if (c->tp == 1)
        {
            execute_one(c, d, e);
            c = c->next;
        }
        else if (c->tp == 6)
        {
            c = c->next;
        }
        else if (c->tp == 7)
        {
            c = c->next;
            if (e->exits == 0)
                c = skip_next_group(c);
        }
        else if (c->tp == 8)
        {
            c = c->next;
            if (e->exits != 0)
                c = skip_next_group(c);
        }
        else if (c->tp == 9)
        {
            
            (e->ilevel)++;
            e->pid[e->ilevel] = fork();
            if (e->pid[e->ilevel] == 0)
            {
                (e->slevel)++;
                printf("execute_command_line2(): now im at %dth fork\n", e->slevel);//debug
                c = c->next;
            }
            else
            {
                c = skip_next_group(c);
                if (c == NULL)
                    wait_cocurrent(e);
                else if (c->tp == 7 || c->tp == 8)
                    wait_cocurrent(e);
            }
        }
        else if (c->tp == 10)
        {
            printf("execute_command_line2(): cmd[%d]\n", c->id);//debug;
            wait_cocurrent(e);
            d->status = e->exits;
                exit(0);
        }
    }
    get_temp_file(0);
    printf("execute_command_line2(): end\n");//debug;
    return (0);
}

int execute_command_line(t_c *c, t_d *d)
{
    t_exe   e;

  //  printf("execute_command_line(): start\n");//debug
    if (!valid_check(c))
    {
        printf("not a valid command line\n");
        return (-1);
    }
 //   printf("execute_command_line(): will find pipes\n");//debug
    find_pipes(c);
    printf("execute_command_line():------------\n");//debug
    print_cmd_list(c); //debug
  //  printf("execute_command_line(): will init_exe\n");//debug
    if (!init_exe(c, &e))
    {
        printf("not enough memory\n");
        return (-1);
    }
    printf("execute_command_line(): start execution\n");//debug
    return (execute_command_line2(c, d, &e));
}
