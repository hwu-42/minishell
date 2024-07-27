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
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#define MAXMM 2

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
char    *strimmed(char *s);

void    prt_env(t_d *d);
int     export_env(t_d *d);
int     unset_env(t_d *d);
int     white_space(char c);
char    *get_name(char *s);
int     my_echo(t_d *d);
t_s     *into_ss(char *s);
void    free_list(t_s **l);
void    remove_env(t_d *d, char *todelete);
int     add_env(t_d *d, char *new);

void    my_pwd(t_d *d);
int     my_cd(t_d *d);

#endif