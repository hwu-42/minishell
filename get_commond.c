#include "minishell.h"

static int  find_unclosed_syntex(char *s, t_st *st);
static int  parse_line(char *s, t_st *st);
char        *get_command(void);
char        *get_eof(char *s);


int spcial_char(char c)
{
    if (*ft_strrchr("'\"<>()|&", c) == c || white_space(c))
        return (1);
    return (0);
}

char    *get_eof(char *s)
{
    int i;
    char    *re;

    printf("get_eof: s: %s\n", s);//debug
    while(white_space(*s))
        s++;
    if (*s == 0)
        return (NULL);
    i = 0;
    while (*(s + i) && !spcial_char(*(s + i)))
        i++;
    printf("get_eof: eof size is %d\n", i);//debug
    re = malloc(i + 1);
    if (re == NULL)
    {
        printf("mem eorror\n");
        return(NULL);
    }
    else
    {
        ft_strlcpy(re, s, i + 1);
        re[i + 1] = 0;
        printf("get_eof: re: %s\nback to caller\n", re);//debug
        return (re);
    }
}
void    print_eofs(void) // debug
{
    printf("print_eofs(): now the first eof is: %s\n", unclosed_eofs(0, NULL));
}

//return situations: 0 for complete, 1 for < error, 2 for << error, 3 for > error, 
//4 for >> error, 5 for | error, 6 for (error, -1 for incomplete input, -2 for unexpected EOF
//inquote = 1 for ' quote, inquote = 2 for ", inquote = 0 for not in quote
static int find_unclosed_syntex(char *s, t_st *st)
{
    char    *eof;
    
    printf("find_unclosed_syntex(): input= %s\n", s); //debug
    while (*s && *s != '<' && *s != '>' && *s != 34 && *s != 39 && *s != '|' && *s != '(' && *s != ')')
    { //debug
        printf("find_unclosed_syntex(): %c is skipped\n", *s);//debug
        s++;
    } //debug
        
    printf("find_unclosed_syntex(): all non syntex skipped, %c\n", *s);//debug
    if (*s == 0)
    {
        if (st->son == 1 || st->don == 1 || unclosed_eofs(0, NULL) || st->pon)
            return (-1);
        else
            return (0);
    }
    printf("find_unclosed_syntex(): find syntex\n");//debug
    if (*s == 34)
    {
        st->don = 1;
        return (parse_line(s + 1, st));
    }
    else if (*s == 39)
    {
        st->son = 1;
        return (parse_line(s + 1, st));
    }
    else if (*s == '<')
    {
        s++;
        while (*s == ' ')
            s++;
        if (*s == 0)
            return (1);
        else if (*s == '<')
        {
            s++;
            printf("find_unclosed_syntex(): << found, search for eof\n");//debug
            eof = get_eof(s);
            printf("find_unclosed_syntex(): i m back\n");//debug
            printf("find_unclosed_syntex(): new eof: %s\nthen\n", eof);//debug
            if (eof == NULL)
                return (2);
            else
            {
                printf("find_unclosed_syntex(): add eof to list ... ");//debug
                unclosed_eofs(1, eof);
                printf("find_unclosed_syntex(): add eof done\n");//debug
                print_eofs();//debug
                while (*s == ' ')
                    s++;
                while (*s != ' ' && *s && *s != '<' && *s != '>' && *s != 34 && *s != 39)
                    s++;
                if (*s)
                    return(find_unclosed_syntex(s, st));
                else
                    return(-1);
            }
        }
        else
            return(find_unclosed_syntex(s, st));
    }
    else if (*s == '>')
    {
        s++;
        while (*s == ' ')
            s++;
        if (*s == 0)
            return (3);
        else if (*s == '>')
        {
            s++;
            while (*s == ' ')
                s++;
            if (*s == 0)
                return (4);
            else
                return(find_unclosed_syntex(s, st));
        }
        else
            return (find_unclosed_syntex(s, st));
    }
    else if (*s == '|')
    {
        s++;
        while (*s == ' ')
            s++;
        if (*s == 0)
            return (-1);
        else if (*s == '|')
            return (5);
        else
            return (find_unclosed_syntex(s, st));
    }
    else if (*s == '(')
    {
        st->pon++;
        return (find_unclosed_syntex(s + 1, st));
    }
    else if (*s == ')')
    {
        if (st->pon > 0)
        {
            st->pon--;
            return (find_unclosed_syntex(s + 1, st));
        }
        else
            return (6);
    }
    else
        return (0);
}

//return situations: 0 for complete, 1 for < error, 2 for > error, 3 for >> error, 
//4 for << error, 5 for | error, 6 for unclosed ', 7 for uclosed ",
//-1 for incomplete input, -2 for unexpected EOF
//consider |on
// 34: ", 39: '
static int    parse_line(char *s, t_st *st)
{
    int re;

    printf("parse_line(): son: %d, don: %d\n", st->son, st->don);//debug
    if (s == NULL)
        return (-2);
    if (*s == 0)
    {
        printf("parse_line(): s = %s\n", s);//debug
        printf("parse_line(): eof: %s\n", unclosed_eofs(0, NULL));//debug
        if (st->son == 1 || st->don == 1 || unclosed_eofs(0, NULL) || st->pon)
            return (-1);
        else
        {
            printf("parse_line(): complete command\n");//debug
            return (0);
        }
    }
    if (st->son == 1) // split into son == 1 and don == 1
    {
        while (*s && *s != 39)
            s++;
        if (*s == 39)
        {
            st->son = 0;
            return(find_unclosed_syntex(s + 1, st));
        }
        else
            return(-1);
    }
    if (st->don == 1)
    {
        while (*s && *s != 34)
            s++;
        if (*s == 34)
        {
            st->don = 0;
            return(find_unclosed_syntex(s + 1, st));
        }
        else
            return(-1);
    }
    if (st->pon)
        return(find_unclosed_syntex(s, st));
    else if (unclosed_eofs(0, NULL))
    {
        if (st->fll && !dif_str(unclosed_eofs(0, NULL), s))
            unclosed_eofs(-1, NULL);
        if (unclosed_eofs(0, NULL) == NULL)
            return (0);
        else
            return (-1);
    }
    else
    { //debug
        printf("parse_line: enclosed\n");//debug
        re = find_unclosed_syntex(s, st);
        if (re == 0 && (st->son == 1 || st->don == 1 || unclosed_eofs(0, NULL) || st->pon))
            return (-1);
        else
            return (re);
    }//debug
}

void    init_status(t_st *s)
{
    s->don = 0;
    s->pon = 0;
    s->son = 0;
    s->n = 0;
    s->aon = 0;
    s->von = 0;
    s->oon = 0;
    s->s = NULL;
    s->fll = 1;
}

//son: single_quote_on, don: double_quote_on
char    *get_command(void)
{
    char    *input;
    char    *temp = NULL;
    char    *tt;
    t_st    st;
    int     n;

    init_status(&st);
    while (1)
    {
        if (temp == NULL)
            input = readline("$> ");
        print_eofs();
        printf("get command(): input= %s\n", input); //debug
        n = parse_line(input, &st);
         if (input == NULL) {
            // ctrl-D: exit the shell
            exit(0);
        }
        printf("get command(): n= %d\n", n); //debug
        if (n == 0)
        {//debug
            printf("get_command(): done\n");//debug
            tt = ft_strjoin(temp, input);
            printf("get_command(): now, temp is %p\n", temp);//debug
            free(temp);
            free(input);
            printf("get_command(): done, input is: %s\n", tt);//debug
            return (tt);
            //return (ft_strjoin(temp, input));
        }//debug
        else if ((n > 0) || n == -2)
        {
            printf("get command: n= %d, input error\n", n); //tbc
            free (input);
            if (temp)
                free (temp);
            temp = NULL;
        }
        else if (n == -1)
        {
            
            tt = ft_strjoin(temp, input);
            free(temp);
            free(input);
            temp = ft_strjoin(tt, "\n");
            free(tt);
            printf("get_command(): now the input is:\n%s\n", temp);//debug
            input = readline("> ");
        }
        else
            printf("get command(): error\n"); //debug
    }
}
