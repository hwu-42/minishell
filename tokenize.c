#include "minishell.h"

// here we deal with only <, <<, >, >>, |, ||, &&, ()
// <if not in quotatin>: |, ||, &&, (, ), marks the end of a command
// <if not in quotatin>: |, ||, &&, (, ), white_spaces marks the end of a argument
// <if not in single quotatin>:$ marks a env var; ::to expand
// <if not in quotatin && not in type 'command'>: marks a wildcard char; ::to expand

// type: 
// ***************************** member of command
// command:  1  *s      1
// argument: 2  *s      0-n
// heredoc:  3  *s      0-n
// output1:  4  *s      1
// output2:  5  *s      1
// ***************************** logical operators
// pipe:     6  null    
// or:       7  null
// and:      8  null
// (:        9  null
// ):        10 null

typedef struct s_token_node
{
    int str;
    int ttp;
    char    *s;
    struct s_token_node *next;
}   t_t;

//tp: command 1;
typedef struct s_command_node
{
    int     tp;
    char    *cmd;
    struct s_command_node   *next;
}   t_c;

void    tokenize(char *s)
{
    printf("%s\n", s);
}



//op: 1 for add, 0 for inquery, -1 for delete, -2 for free all
t_t *commands(int op, t_t *tk)
{}