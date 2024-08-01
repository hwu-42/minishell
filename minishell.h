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
#define MAXMM 1024
#define ARGU 2


/*spec 01 start*/
// here we deal with only <, <<, >, >>, |, ||, &&, ()
// <if not in quotatin>: |, ||, &&, (, ), marks the end of a command
// <if not in quotatin>: |, ||, &&, (, ), white_spaces marks the end of a argument
// <if not in single quotatin>:$ marks a env var; ::to expand
// <if not in quotatin && not in type 'command'>: marks a wildcard char; ::to expand

// type: 
// ***************************** member of command
// command:  0  *s      1
// argument: 1  *s      0-n
// ifile:    2  *s      0-n       <
// heredoc:  3  *s      0-n       <<EOF
// output1:  4  *s      0,1       >
// output2:  5  *s      0,1       >>
// ***************************** logical operators
// pipe:     6  null    
// or:       7  null
// and:      8  null
// (:        9  null
// ):        10 null
/*spec 01 end*/

//list of command prpared for execution:
//tp(type) as in spec 01;
//cmd: command + args, first is executable, others are expended string as arguments
//cmd is a pointer to area of pointer which point to strings, the NULL indicate the end of this area
//heredoc: expaned string as stdin input when is executable is running
//ifile: input file as stdin input when is executable is running
//otype: output type, -1 for write to file; -2 for append to file; 1 for stdout; other as pipe num;
//ofile: output file name, NULL when otype > 0;
typedef struct s_command_node
{
    int     tp;
    char    **cmd;
    char    *heredoc;
    char    *ifile;
    int     otype;
    char    *ofile;
    struct s_command_node   *next;
    struct s_command_node   *last;
}   t_c;

// son: ' is on, don " is on, pon ( is on, full_line parsing a full_line?
// oon: || is on, aon: && is on, von: | is on vertical-bar
typedef struct s_status
{
    int     son;
    int     don;
    int     pon;
    int     oon;
    int     aon;
    int     von;
    int     fll;
    int     n;
    char    *s;
}   t_st;

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


//str: 0 if not a literal string, 1 literal string
typedef struct s_token_node
{
    int str;
    int ttp;
    char    *s;
    struct s_token_node *next;
}   t_t;


void    mfree(void * p);
void    *mmalloc(size_t t);
int    heap_mngr(void *new, int add);
void    clean_heaps(void ***p);

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
char    *get_env_value(t_d *d, char *key);

void    my_pwd(t_d *d);
int     my_cd(t_d *d);
char    *get_pwd(t_d *d);
void    concat_path(char *dest, char *s);

int     valid_check(t_c *c);

#endif