#include "minishell.h"

//*****!!! key is not freed in the this funciton
char    *get_env_value(t_d *d, char *key);


// **********!!! returned char* must be freed in calling function
//env name can only contain alpnum _, can not star with num
//in: inquotation, 0 for not, 1 for ', 2 for "
//string *s start with $
char *get_env_name(char *s)
{
    int i;
    char    *re;

    i = 1;
    while (s[i])
    {
        if (!ft_isalnum(s[i]) && s[i] != '_')
            break;
        i++;
    }
    re = malloc(i);
    if (re == NULL)
        return (NULL);
    re[i - 1] = 0;
    i--;
    while (i > 0)
    {
        re[i - 1] = s[i];
        i--;
    }
    return (re);
}