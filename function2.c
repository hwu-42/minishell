#include "minishell.h"

void    print_list(t_s *list); //debug

//in: inquotation, 0 for not, 1 for ', 2 for "
int dequoted_size(char *s)
{
    int count;
    int inquote;

    //printf("dequoted_size(): start to count string %s\n", s);//debug
    count = 0;
    inquote = 0;
    while (*s)
    {
        if (inquote == 2 && *s == '\"')
            inquote = 0;
        else if (inquote == 1 && *s == '\'')
            inquote = 0;
        else if (inquote == 0 && *s == '\"')
            inquote = 2;
        else if (inquote == 0 && *s == '\'')
            inquote = 1;
        else
            count++;
        s++;
    }
    //printf("dequoted_size(): size is %d\n", count);//debug
    return (count);
}

// dequoted *s will be stored in *t
void    dequoted_string(char *s, char *t)
{
    int inquote;

    inquote = 0;
    while (*s)
    {
        if (inquote == 2 && *s == '\"')
            inquote = 0;
        else if (inquote == 1 && *s == '\'')
            inquote = 0;
        else if (inquote == 0 && *s == '\"')
            inquote = 2;
        else if (inquote == 0 && *s == '\'')
            inquote = 1;
        else
            *t++ = *s;
        s++;
    }
    *t = 0;
}

//non: is -n on of off
int    my_echo(t_d *d)
{
    t_s     *ss;
    t_s     *temp;
    char    *s;
    int     non;

    non = 0;
    printf("my_echo(): received string is %s\n", d->s);//debug
    ss = into_ss(d->s);
    printf("my_echo(): splited ");//debug
    print_list(ss);//debug
    temp = ss->next;
    if (temp)
    {
        s = malloc(dequoted_size(temp->s) + 1);
        if (s == NULL)
            return (0);
        dequoted_string(temp->s, s);
        if (s[0] == '-')
            if (s[1] == 'n')
                if (s[2] == 0)
                {
                    non = 1;
                    temp = temp->next;
                }
    }
    printf("my_echo(): result for echo is:\n");//debug
    while (temp)
    {
        s = malloc(dequoted_size(temp->s) + 1);
        if (s == NULL)
            return (0);
        dequoted_string(temp->s, s);
        printf("%s", s);
        free(s);
        if (temp->next)
            printf(" ");
        temp = temp->next;
    }
    if (!non)
        printf("\n");
    wfree_list(&ss);
    return (1);
}

char    *get_env_value(t_d *d, char *key)
{
    char    **env;
    char    *re;

    env = *(d->env);
    printf("my_pwd(): %p\n", env); //debug
    while (*env)
    {
        if (dif_str(key, get_name(*env)))
            env++;
        else
            break;
    }
    re = *env;
    while (*re != '=')
        re++;
    re++;
    return (re);
}

void    my_pwd(t_d *d)
{
    printf("%s\n", get_pwd(d));
}

char    *get_pwd(t_d *d)
{
    char    **env;

    env = *(d->env);
    printf("my_pwd(): %p\n", env); //debug
    while (*env)
    {
        if (dif_str("PWD", get_name(*env)))
            env++;
        else
            break;
    }
    return (ft_strdup(*env + 4));
}

void    remove_back_slash(char *s)
{
    int i;

    i = 0;
    if (s == NULL)
        return ;
    while (*s)
    {
        s++;
        i++;
    }
    s--;
    i--;
    while (*s == '/' && i != 0)
    {
        *s-- = 0;
        i--;
    }
}

//this function used to concate char s to dest, both consider as path
//this function does not check path exist or not, can be checked with opendir()
void    concat_path(char *dest, char *s)
{
    char    *i;

    printf("concat_path(): dest: %s, s: %s\n", dest, s);//debug
    i = dest;
    while (*i)
        i++;
    
    while (*s)
    {
        while (*s == '/')
            s++;
        printf("concat_path(): now the s: %s\n", s);//debug
        if (*s == '.')
        {
            if (s[1] == '.')
            {
                if (s[2] == '/' || s[2] == 0)
                {
                    s += 2;
                    if (i > dest)
                    {
                        *--i = 0;
                        i--;
                        while (*i != '/')
                            *i-- = 0;
                        i++;
                    }
                }
                else
                {
                    while (*s != '/' && *s)
                        *i++ = *s++;
                    if (*s == '/')
                        *i++ = *s++;                    
                }
            }
            else if (s[1] == '/' || s[1] == 0)
            {
                s++;
            }
            else
            {
                while (*s != '/' && *s)
                    *i++ = *s++;
                if (*s == '/')
                    *i++ = *s++;
            }
        }
        else
        {
            //printf("concat_path(): dest: %s, s: %s\n", dest, s);//debug
            while (*s != '/' && *s)
                *i++ = *s++;
            //printf("concat_path(): now the dest: %s\n", dest);//debug
            if (*s == '/')
                *i++ = *s++;
            //printf("concat_path(): now the dest: %s\n", dest);//debug
        }
        *i = 0;
        //printf("concat_path(): now the dest: %s\n", dest);//debug
    }
}

int parse_path(t_d *d, char *s, char *old, char *new)
{
    DIR *dir;
    int len;
    
    if (*s == 0)
        return (0);
    len = ft_strlen(s) + ft_strlen(old) + ft_strlen(get_env_value(d, "HOME")) + 1;
    *new++ = 'P';
    *new++ = 'W';
    *new++ = 'D';
    *new++ = '=';
    printf("parse_path(): s=%s, new=%s, old=%s\n", s, new, old);//debug
    if (*s == '/')
        ft_strlcat(new, "/", len);
    else if (*s == '~' && (s[1] == 0 || s[1] == '/'))
    {
        ft_strlcat(new, get_env_value(d, "HOME"), len);
        ft_strlcat(new, "/", len);
        s++;
    }
    else
    {
        ft_strlcat(new, old, len);
        ft_strlcat(new, "/", len);
    }
    concat_path(new, s);
    printf("parse_path(): after combine path = %s\n", new);//debug
    remove_back_slash(new);
    printf("parse_path(): after combine path = %s\n", new);//debug
    dir = opendir(new);
    if (dir == NULL)
    {
        printf("minishell: cd: %s: no such directory\n", new);
        return(0);
    }
    closedir(dir);
    return (1);
}

int my_cd(t_d *d)//change to use t_c *c
{
    char    **env;
    char    *new;
    t_s     *ss;

    ss = into_ss(d->s + 2);
    if (ss == NULL)
        return(0);
    if (ss)
    {
        if (ss->next)
        {
            printf("Too many args for cd command\n");
            return (0);
        }
    }
    new = ft_strdup(ss->s);
    dequoted_string(ss->s, new);
    env = *(d->env);
    while (*env)
    {
        if (dif_str("PWD", get_name(*env)))
            env++;
        else
            break;
    }
    free(d->s);
    d->s = malloc(ft_strlen(*env) + ft_strlen(new) + 2);
    if (d->s == NULL)
        return (0);
    ft_memset(d->s, 0, ft_strlen(*env) + ft_strlen(new) + 2);
    if (parse_path(d, new, *env + 4, d->s) == 0)
        return (0);
    remove_env(d, "PWD");
    printf("my_cd(): will add env: %s\n", d->s);//debug
    add_env(d, d->s);
    return (1);
}