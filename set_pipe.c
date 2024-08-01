#include "minishell.h"

//the pipes index start from 0 for command 0 
//i used to keep track of the index of 
//pipeid[i] will be use for command[i] as input pipe.

void    set_pipe(t_c *c)
{
    t_c *p;

    while (c)
    {
        p = c;
        while (p)
        {
            if (p->tp == 6)
                break;
            p = p->next;
        }
        if (p == NULL)
            c->otype = 1;
        else
        {
            while(p)
            {
                if (p->tp == 1)
                    break;
                p = p->next;
            }
            if (p == NULL)
                printf("check the program, it's bad\n");
            else
                c->otype = p->id;
        }
        c = c->next;
    }
}