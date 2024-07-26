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

typedef struct s_data
{
    char    ***env;
    char    *s;
    int         syn;
    int         used;
}   t_d;

typedef struct s_string_list
{
    struct s_string_list     *next;
    char    *s;
}   t_s;

/*
void    mfree(void * p);
void    *mmalloc(size_t t);
int    heap_mngr(void *new, int add);
void    clean_heaps(void ***p);
*/

char    *get_command(void);
char    *unclosed_eofs(int add, char *eof);
int     dif_str(char *s, char *t);

void    prt_env(t_d *d);
int     export_env(t_d *d);
int     unset_env(t_d *d);
int     white_space(char c);

#endif