#include "minishell.h"

// pipe:     6  null    
// or:       7  null
// and:      8  null
// (:        9  null
// ):        10 null

int valid_check(t_c *c)
{
    if (c)
        if (c->tp != 1)
            return (0);
    while (c)
    {
        if (c->tp == 1)
            if (c->next)
                if (c->next->tp == 1)
                    return (0);
        else if (c->tp == 6)
            if (c->next == NULL)
                return (0);
            if (c->next->tp == 6 || c->next->tp == 7 || c->next->tp ==8)
                return (0);
        else if (c->tp == 7)
            if (c->next == NULL)
                return (0);
            if (c->next->tp == 6 || c->next->tp == 7 || c->next->tp == 8 || c->next->tp ==10)
                return (0);
        else if (c->tp == 8)
            if (c->next == NULL)
                return (0);
            if (c->next->tp == 6 || c->next->tp == 7 || c->next->tp == 8 || c->next->tp == 10)
                return (0);
        else if (c->tp == 9)
            if (c->next == NULL)
                return (0);
            if (c->next->tp == 6 || c->next->tp == 7 || c->next->tp == 8 || c->next->tp == 10)
                return (0);
        else if (c->tp == 10)
            if (c->next)
                if (c->next->tp == 1 || c->next->tp == 9)
                    return (0);
        else
            c = c->next;
    }
    return (1);
}

