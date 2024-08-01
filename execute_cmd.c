#include "minishell.h"

int init_pipe(int **p)
{}

void    execute_one(t_c *c, t_d *d, t_exe *e)
{
    int pid;

    if (c->tp == 9)
    {
        c = c->next;
        pid =fork();
        e->ilevel++;
    }

}

int execute_cmd(t_c *c, t_d *d, int slevel)
{
    int pipeid[MAXMM][2];
    int exits;
    pid_t   pid;
    int ilevel;

    if (!valid_check(c))
    {
        printf("not a valid command line\n");
        return (0);
    }
    if (!init_pipe(pipeid))
    {
        printf("not enougf memory\n");
        return (0);
    }
    while (c)
    {
        if (c->tp == 9)
        {
            c = c->next;
            pid = fork();
            ilevel++;
            if (pid == 0)
            {
                while (ilevel > slevel)
                {
                    execute_one(c, d, ilevel);
                    c = c->next;
                }
                return (0);
            }
            else
            {
                while (c)
                {
                    if (c->tp == 9)
                        ilevel++;
                    if (c->tp == 10)
                        ilevel--;
                    c = c->next;
                    if (ilevel == slevel)
                        break;
                }
                

            }
        }
        if (c->tp == 10)
            level--;
        c = c->next;
    }
}