#include "minishell.h"

int     head_match(char *s, char *pattern);

int     get_file_num(t_d *d)
{
    int count;
    DIR *dir;

    count = 0;
    dir = opendir(get_env_value(d, "PWD"));
    if (dir == NULL)
    {
        perror("opendir");
        return (-1);
    }
    while (readdir(dir))
        count++;
    return (count);
}

char    **get_file_list(t_d *d)
{
    struct dirent *entry;
    char **filenames;

    DIR *dir;
    dir = opendir(get_env_value(d, "PWD"));
    if (dir == NULL) {
        perror("opendir");
        return NULL;
    }
    filenames = malloc(sizeof(char *) * (get_file_num(d) + 1));
    while ((entry = readdir(dir)) != NULL) 
    {
        if (dif_str(entry->d_name, ".") && !dif_str(entry->d_name, ".."))
        {
            *filenames = malloc(strlen(entry->d_name) + 1);
            ft_strlcpy(*filenames, entry->d_name, ft_strlen(entry->d_name) + 1);
            filenames++;
        }
    }
    filenames = NULL;
    closedir(dir);
    return filenames;
}

int     find_active_star(char *s)
{
    int don;
    int son;

    son = 0;
    don = 0;
    while (*s)
    {
        if(*s == '*' && !son && !don)
            return (1);
        else if (*s == 34)
            don = 1 - don;
        else if (*s == 39)
            son = 1 - son;
    }
    return (0);
}

t_t *add_it_to_token(t_t *head, char *s, int str, int type)
{
    while (head)
        head = head->next;
    head = malloc(sizeof(t_t));
    if (head == NULL)
        return (NULL);
    head->s = ft_strdup(s);
    head->str = str;
    head->ttp = type;
    head->next = NULL;
    return (head);
}

//this funciton will change the pointer in the calling funciton either
char    *get_word(char **p)
{
    int i;
    char    *re;

    printf("get_word(): a the string is: %s\n", *p);//debug
    if (p == NULL)
        return (NULL);
    if (*p == NULL)
        return (NULL);
    while (**p == '*' && **p)
        (*p)++;
    printf("get_word(): b the string is: %s\n", *p);//debug
    i = 0;
    while ((*p)[i] != '*' && (*p)[i])
        i++;
    printf("get_word(): c the string is: %s\n", *p);//debug
    re = malloc(i + 1);
    if (re == NULL)
        return (NULL);
    i = 0;
    while (**p != '*' && **p)
    {
        re[i++] = **p;
        (*p)++;
    }
    re[i] = 0;
    return (re);
}

char    *reverse_string(char *s)
{
    char    *re;
    int     n;

    n = ft_strlen(s);
    re = malloc(n + 1);
    re[n--] = 0;
    while (n >= 0)
    {
        re[n] = *s++;
        n--;
    }
    return (re);
}

int     tail_match(char *s, char *pattern)
{
    char    *rs;
    char    *rp;
    int     re;

    rs = reverse_string(s);
    rp = reverse_string(pattern);
    re = head_match(rs, rp);
    free(rs);
    free(rp);
    return(re);
}

int     head_match(char *s, char *pattern)
{
    if (*pattern == '*' || *pattern == 0)
        return (1);
    if (*s != *pattern)
        return (0);
    else
    {
        while (*s == *pattern && *s && *pattern != '*')
        {
            s++;
            pattern++;
        }
        if (*s != *pattern && *pattern != '*')
            return (0);
        else
            return (1);
    }
}
int     match(char *s, char *pattern)
{
    char    *word;

    printf("match(): headmatch %d, tailmatch %d\n", head_match(s, pattern), tail_match(s, pattern));//debug
    if (!head_match(s, pattern) || !tail_match(s, pattern))
        return (0);
    printf("match(): to fetch word\n");//debug
    word = get_word(&pattern);
    printf("match(): the word is: %s\n", word);//debug
    while (word)
    {
        if (*word == 0)
            break;
        printf("match(): the word is: %s", word);//debug
        s = ft_strnstr(s, word, ft_strlen(s));
        if (s == NULL)
            return (0);
        s += ft_strlen(word);
        free(word);
        word = get_word(&pattern);
    }
    return (1);
}
void    free_token(t_t *t)
{
    free(t->s);
    free(t);
}
void    link_token(t_t *head, t_t *t)
{
    while (head)
        head = head->next;
    head = t;
}

void    copy_token(t_t *src, t_t *dest)
{
    dest->s = src->s;
    dest->ttp = src->ttp;
    dest->str = src->str;
    dest->next = src->next;
}

//f is point to file name string
//return 1 for success, 0 for no expansion done, -1 for memory error
int    star_substitude(t_t *tk, t_d *d)
{
    char    **f;
    t_t     *file_match;
    t_t     *next;

    next = tk->next;
    if (tk->str || !find_active_star(tk->s) || tk->ttp != ARGU)
        return (0);
    f = get_file_list(d);
    file_match = NULL;
    while (*f)
    {
        if (match(*f, tk->s))
            if (add_it_to_token(file_match, *f, 1, ARGU) == NULL)
                return (-1);
        f++;
    }
    if (file_match == NULL)
        return (0);
    free(tk->s);
    copy_token(file_match, tk);
    free_token(file_match);
    link_token(tk, next);
    return (1);
}
/*

int main(void)
{
    char    *input;
    char    **list;

    input = readline("input word pair to be compared, seperated by space:\n");
    while (strcmp(input, "exit"))
    {
        list = ft_split(input, ' ');
        printf("%d\n", match(list[0], list[1]));
        input = readline("input word pair to be compared, seperated by space:\n");
    }
}


*/