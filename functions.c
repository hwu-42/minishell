#include "minishell.h"

void    print_list(t_s *list); //debug

int     white_space(char c)
{
    if (c == ' '|| (c > 8 && c < 14))
        return (1);
    return (0);
}

void    prt_env(t_d *d)
{
    char    **ent;

    ent = *(d->env);
    while (*ent != NULL)
        printf("%s\n", *(ent++));
}

int get_len(char *s)
{
    int i;
    int inquote;
    
    inquote = 0;
    i = 0;
    while (s[i] && ((!inquote && !white_space(s[i])) || inquote))
    {
        if (inquote == 2 && s[i] == '\"')
            inquote = 0;
        else if (inquote == 1 && s[i] == '\'')
            inquote = 0;
        else if (inquote == 0 && s[i] == '\"')
            inquote = 2;
        else if (inquote == 0 && s[i] == '\'')
            inquote = 1;
        i++;
    }
    return (i);
}

char    *sub_str(char *s, int i)
{
    char    *re;
    int     j;

    printf("sub_str(): string to sub is %s\n", s);//debug
    re = malloc(i + 1);
    if (re == NULL)
        return (NULL);
    j = 0;
    while (j < i)
    {
        re[j] = s[j];
        j++;
    }
    re[j] = 0;
    printf("sub_str(): substring is %s\n", re);//debug
    return (re);
}

int add_node(t_s **list, char *s)
{
    t_s *temp;
    
    //print_list(*list);//debug
    if (*list == NULL)
    {
        *list = malloc(sizeof(t_s));
        if (*list == NULL)
            return (0);
        else
        {
            (*list)->next = NULL;
            (*list)->s = s;
            print_list(*list);//debug
            return (1);
        }
    }
    else if ((*list)->next == NULL && (*list)->s == NULL)
    {
        (*list)->s = s;
        return (1);
    }
    temp = *list;
    while (temp->next != NULL)
        temp = temp->next;
    return (add_node(&temp->next, s));
}
void wfree_list(t_s **l)
{
    t_s *temp;

    while (*l != NULL)
    {
        if ((*l)->s != NULL)
            free((*l)->s);
        temp = (*l)->next;
        free(*l);
        *l = temp;
    }
}

//split string into list of key=value
t_s    *into_ss(char *s)
{
    int i;
    t_s *re;

    if (s == NULL)
        return (NULL);
    if (*s == 0)
        return (NULL);
    re = malloc(sizeof(t_s));
    if (re == NULL)
        return(NULL);
    re->next = NULL;
    re->s = NULL;
    printf("into_ss(): string to split is %s\n", s);//debug
    while (*s)
    {
        while (white_space(*s))
            s++;
        printf("into_ss(): now left string is %s\n", s);//debug
        i = get_len(s);
        printf("into_ss(): key=value string len is %d\n", i);//debug
        if (!add_node(&re, sub_str(s, i)))
        {
            printf("mem error\n");
            wfree_list(&re);
            return (NULL);
        }
        print_list(re);//debug
        s += i;
    }
    return (re);
}

//this function check if the charactor is allowed for env var name
//@ is allowed as expending with @(var_name) is allowed
// int in meaning is the char c in a quotation or not
int correct_char(int in, char c)
{
    if (in == 1 && (ft_isalnum(c) || c == '_' || c == '\''))
        return (1);
    if (in == 2 && (ft_isalnum(c) || c == '_' || c == '\"'))
        return (1);
    if (in == 0 && (ft_isalnum(c) || c == '_' || c == '\'' || c == '\"'))
        return (1);
    if ((in == 0 || in == 2) && c == '@')
        return (1);
    return (0);
}

//env name can only contain alpnum _, can not star with num
//in: inquotation, 0 for not, 1 for ', 2 for "
int valid_env(char *s)
{
    int inquote;

    if (s == NULL)
        return (0);
    if (!ft_isalpha(*s) && *s != 34 && *s != 39 && *s != '_')
        return (0);
    inquote = 0;
    while(correct_char(inquote, *s))
    {
        if (inquote == 2 && *s == '\"')
            inquote = 0;
        else if (inquote == 1 && *s == '\'')
            inquote = 0;
        else if (inquote == 0 && *s == '\"')
            inquote = 2;
        else if (inquote == 0 && *s == '\'')
            inquote = 1;
        s++;
    }
    if (*s == '=')
        return (1);
    if (*s == 0)
        return (0);
    printf("valid_env(): string is valid\n");//debug
    return (-1);
}
//in: inquotation, 0 for not, 1 for ', 2 for "
int regularized_size(char *s)
{
    int count;
    int inquote;

    printf("regularized_size(): start to count string %s\n", s);//debug
    count = 0;
    while (*s != '=')
    {
        if (*s != 34 && *s != 39)
            count++;
        s++;
    }
    count++;
    s++;
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
    printf("regularized_size(): size is %d\n", count);//debug
    return (count);
}
void    load_env(char *s, char *t)
{
    int inquote;
    char    *temp;//debug

    temp = t;
    while (*s != '=')
    {
        if (*s != 34 && *s != 39)
            *t++ = *s;
        s++;
    }
    *t++ = *s;
    s++;
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
    printf("load_env(): regularized env is %s\n", temp);//debug
}

int add_env(t_d *d, char *new)
{
    int i;
    int j;
    char    **nvs;

    nvs = *(d->env);
    i = 0;
    while (*nvs)
    {
        i++;
        nvs++;
    }
    printf("add_env(): number of existing env is %d\n", i);//debug
    nvs = malloc(sizeof(char *) * (i + 2));
    if (nvs == NULL)
        return (0);
    j = 0;
    while (j < i)
    {
        nvs[j] = (*(d->env))[j];
        j++;
    }
    nvs[j] = ft_strdup(new);
    nvs[j + 1] = NULL;
    printf("add_env(): new env list is ready, will free old list\n");//debug
    free(*(d->env));
    *(d->env) = nvs;
    printf("add_env(): new env address is %p\n", nvs);//debug
    printf("add_env(): old env list is freed, new list loaded\n");//debug
    return (1);    
}

void    print_list(t_s *list) //debug
{
    printf("list is:\n");
    while (list)
    {
        printf("%s\n", list->s);
        list = list->next;
    }
}

//used to get name for both env entry of input env name
char    *get_name(char *s)
{
    int count;
    char    *re;

    //printf("get_name(): will get the name from: %s ... \n", s);//debug
    re = s;
    count = 0;
    while (*s != '=' && *s != 0)
    {
        if (*s != 34 && *s != 39)
            count++;
        s++;
    }
    //printf("get_name(): name lenth: %d, string is %s ... \n", count, re);//debug
    s = re;
    //printf("get_name(): name lenth: %d, string is %s ... \n", count, s);//debug
    re = malloc(count + 1);
    if (re == NULL)
        return (NULL);
    re[count] = 0;
    count = 0;
    while (*s != '=' && *s != 0)
    {
        if (*s != 34 && *s != 39)
            re[count++] = *s;
        s++;
    }
    //printf("get_name(): name: %s\n", re);//debug
    return (re);
}
//todelete is the name of the env
void    remove_env(t_d *d, char *todelete)
{
    char    **env;

    printf("remove_env(): env key to delete is %s\n", todelete);//debug
    env = *(d->env);
    while (*env)
    {
        if (dif_str(todelete, get_name(*env)))
            env++;
        else
            break;
    }
    printf("remove_env(): the pointer point to %p, %s\n", *env, *env);//debug
    if (*env)
    {
        free(*env);
        while (env[1])
        {
            *env = env[1];
            env++;
        }
        *env = NULL;
        return ; //debug
    }
    printf("remove_env(): did not find the env key to delete %s\n", todelete);//debug
}

int unset_env(t_d *d)
{
    t_s     *ss;
    t_s     *temp;
    char    *key_todelete;

    printf("unset_env(): received string is %s\n", d->s);//debug
    ss = into_ss(d->s);
    printf("unset_env(): splited ");//debug
    print_list(ss);//debug
    temp = ss;
    while (temp)
    {
        if (valid_env(temp->s) == 0)
        {
            key_todelete = get_name(temp->s);
            printf("unset_env(): env key to be deleted is %s\n", key_todelete);//debug
            remove_env(d, key_todelete);
            temp = temp->next;
        }
    }
    wfree_list(&ss);
    return (1);
}

int    export_env(t_d *d)
{
    t_s     *ss;
    t_s     *temp;
    char    *new;

    printf("export_env(): received string is %s\n", d->s);//debug
    ss = into_ss(d->s);
    print_list(ss);//debug
    temp = ss;
    while (temp)
    {
        if (valid_env(temp->s) == 1)
        {
            new = malloc(regularized_size(temp->s) + 1);
            if (new == NULL)
                return (0);
            load_env(temp->s, new);
            remove_env(d, get_name(new));
            add_env(d, new);
        }
        else if (valid_env(temp->s) == -1)
            printf("'%s': not a valid indentifier\n", temp->s);
        temp = temp->next;
    }
    wfree_list(&ss);
    return (1);
}
