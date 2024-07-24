#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#define MAXMM 1024

/*
//syn = 1 for ', 2 for ", 3 for <<
typedef struct s_unclosed_syntex
{
    t_unclose   *next;
    t_unclose   *last;
    int         syn;
    int         used;
}   t_unclose;*/

/*
void    mfree(void * p);
void    *mmalloc(size_t t);
int    heap_mngr(void *new, int add);
void    clean_heaps(void ***p);
*/

char    *get_command(void);
char    *unclosed_eofs(int add, char *eof);
int     dif_str(char *s, char *t);

#endif