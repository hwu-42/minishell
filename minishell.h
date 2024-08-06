#ifndef MINISHELL_H

# define MINISHELL_H

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
#include <errno.h>
#define MAXMM 1024
#define ARGU 2


#define CMD  0
#define ARG  1
#define IFIL 2
#define HDOC 3
#define OUT1 4
#define OUT2 5
#define PIP  6
#define OR   7
#define AND  8
#define PAR1 9
#define PAR2 10

typedef	struct t_list
{
	char			*token;
	int				type;
	struct t_list	*prev;
	struct t_list	*next;
}	t_list;

typedef	struct
{
	char	*input;
	t_list	**head;
	int		*j;
	int		*i;
	char	word[1024];
	char	*token;
}	DollarSignParams;

typedef struct
{
	char *input;
	t_list **head;
	char token[1024];
	int j;
}	QuoteParams;

typedef struct
{
	char *input;
	t_list **head;
	int *i;
	int *j;
	char token[1024];
}	WordParams;

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

//list of command prepared for execution:
//id: should start from 3, corresponding the pipe it is using, as output type number < 3 
//      are reserved for other output type.
//tp(type) as in spec 01;
//cmd: command + args, first is executable, others are expended string as arguments
//cmd is a pointer to area of pointer which point to strings, the NULL indicate the end of this area
//heredoc: expaned string as stdin input when is executable is running
//ifile: input file as stdin input when is executable is running
//otype: output type, -1 for write to file; -2 for append to file; 1 for stdout; other as pipe num;
//ofile: output file name, NULL when otype > 0;
typedef struct s_command_node
{
    int     id;
    int     tp;
    char    **cmd;
    char    *heredoc;
    char    *ifile;
    int     otype;
    char    *ofile;
    struct s_command_node   *next;
    struct s_command_node   *pre;
}   t_c;

// son: ' is on, don " is on, pon ( is on, full_line parsing a full_line?
// oon: || is on, aon: && is on, von: | is on vertical-bar
//cmdl: is parsing commond line, 1 for parsing command line, 0 for parsing heredoc content
typedef struct s_status
{
    int     cmdl;
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
    int     status;
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

//slevel, the start level of the current command block
//ilevel, the level at present
//* if after execute_one() slevel = i level,
//  current shell should wait() all pid and return
//  ilevel and slevel both start form 0, when encounter '(', fork() slevel=ilevel++;
typedef struct s_status_of_current_execution
{
    int slevel;
    int ilevel;
    int pipeid[MAXMM][2];
    int exits;
}   t_exe;

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
void    wfree_list(t_s **l);
void    remove_env(t_d *d, char *todelete);
int     add_env(t_d *d, char *new);
char    *get_env_value(t_d *d, char *key);

void    my_pwd(t_d *d);
int     my_cd(t_d *d);
char    *get_pwd(t_d *d);
void    concat_path(char *dest, char *s);

int     valid_check(t_c *c);


int	ft_strcmp(const char *s1, const char *s2);
size_t ft_strlen(const char *str);
int ft_isalnum(int c);
void *ft_memcpy(void *dst, const void *src, size_t n);
char *ft_strdup(const char *s1);
t_list *create_node(const char *token, int type);
void	concatenate_tokens(char **dest, const char *src1, const char *src2);
t_list *find_last_node(t_list *head);
void append_node(t_list **head, const char *token, int type);
int ft_is_space(char c);
int	is_command(const char *token);
void set_type(t_list **head, const char *token, int is_first);
void add_token(t_list **head, char *token, int *j, int is_first, int combine);
int is_operator(char c);
void handle_dollar_sign_in_word(WordParams *params, int is_first);
int process_word_loop(WordParams *params, int is_first, int *is_env_var);
int process_word(char *input, t_list **head, int start, int is_first);
void	get_operator_token(char *input, char *token, int *i);
void	append_operator_token(char *token, t_list **head);
int	process_operator(char *input, t_list **head, int start);
int	handle_dollar_sign(DollarSignParams params, int i, char quote_char);
void process_quote_body(QuoteParams *params, char quote_char, int *i, int is_first);
int	process_quotes(char *input, t_list **head, int start, int is_first);
void	process_token(char *input, t_list **head, int *i, int *is_first);
void	tokenize_and_classify(char *input, t_list **head);
void	free_list(t_list *head);
#endif
