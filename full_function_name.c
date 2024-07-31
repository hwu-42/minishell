#include "minishell.h"

char    *find_name_in_folder(char *folder, char *s)
{
    DIR *dir;
    char    *entry;
    char    *re;

    dir = opendir(folder);
    if (dir == NULL)
    {
        perror("opendir");
        return NULL;
    }
    while ((entry = readdir(dir)) != NULL) 
    {
        if (ft_strlen(entry) == ft_strlen(s) && ft_strncmp(entry, s, ft_strlen(s)))
        {
            re = ft_strjoin(folder, s);
            closedir(dir);
            if (re == NULL)
                retrun (NULL);
            return(re);
        }
    }
    close(dir);
    return (NULL);
}
char    *find_in_path(char *s, t_d *d)
{
    char    *fds;
    char    *full_name;
    
    full_name = NULL;
    fds = ft_split(get_env_value(d, "PATH"), ':');
    while (*fds)
    {
        full_name = find_name_in_folder(fds, s);
        if (full_name)
            break;
    }
    return (full_name);
}

char    *full_function_name(char *s, t_d *d)
{
    char    *re;
    int     n;

    if (s == NULL)
        return (NULL);
    if (*s == '/')
        return (ft_strdup(s));
    else if (str_strchr(s, '/'))
    {
        n = ft_strlen(get_pwd(d)) + ft_strlen(s) + 3;
        re = malloc (n);
        if (re == NULL)
            return (NULL);
        ft_strlcat(re, get_pwd(d), n);
        concat_path(re, s);
    }
    else
        re = find_in_path(s, d);
    return (re);
}