#include    "minishell.h"

void    print_heap(void ***p); //debug

void    clean_heaps(void ***p)
{
    int i;
    int j;

    i = 0;
    while (i < MAXMM)
    {
        if (p[i] == NULL)
            break ;
        j = 0;
        while (j < MAXMM)
        {
            if ((p[i])[j] != NULL)
                free((p[i])[j]);
            j++;
        }
        free (p[i]);
        i++;
    }
}

void    unregister(void ***p, void *new)
{
    int i;
    int j;

    i = 0;
    while (i < MAXMM)
    {
        if (p[i] == NULL)
            break ;
        j = 0;
        while (j < MAXMM)
        {
            if ((p[i])[j] == new)
                break;
            j++;
        }
        if (j != MAXMM)
        {
            p[i][j] = NULL;
            free (new);
            break ;
        }
        i++;
    }
}

//return -1 for now space malloc fail, -2 for reaching capability limit
//else for the cummulated space num, e.g. num for p[i][j] is i*MAXMM + j
int find_space(void ***p)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    while (i < MAXMM)
    {
        if (p[i] == NULL)
        {
            printf("find_space(): virgin find, i = %d\n", i);//debug
            break;
        }
        while (j < MAXMM)
        {
            printf("find_space(): ckecking p[%d][%d]: %p\n", i, j, p[i][j]);//debug
            if (p[i][j] == NULL)
                break;
            j++;
        }
        if (j != MAXMM)
            break;
        j = 0;
        i++;
    }
    if (i == MAXMM)
        return (-2);
    if (p[i] == NULL)
    {
        p[i] = malloc(sizeof(void *) * MAXMM);
        if (p[i] == NULL)
            return (-1);
        k = 0;
        while (k < MAXMM)
        {
            p[i][k] = NULL;
            k++;
        }
    }
    return (i * MAXMM + j);
}

//add = 1 for add new, 0 for free address, -1 for free all
//return value to be defined, -1 for add fail, positive num for add success, -2 for clean success
int    heap_mngr(void *new, int add)
{
    static void **p[MAXMM];
    int         first_space;

    if (add)
    {
        first_space = find_space(p);
        printf("heap_mnger(): find spece num is %d, meaning (%d, %d)\n", first_space, first_space/MAXMM, first_space%MAXMM);
        if (first_space == -1)
        {
            printf("heap_mnger(): memory error\n");
            return (-1);
        }
        else if (first_space == -2)
        {
            printf("heap_mnger(): used too much memory\n");
            return (-1);
        }
        else
        {
            p[first_space / MAXMM][first_space % MAXMM] = new;
            return (first_space);
        }
    }
    else if (add == 0)
    {
        unregister(p, new);
        return (-2);
    }
    else
    {
        clean_heaps(p);
        return (-2);
    }
}

//return -1 for fail to allocate heap
void    *mmalloc(size_t t)
{
    void    *p;
    int     i;
    
    p = malloc(t);
    if (p == NULL)
        return (p);
    else
    {
        i = heap_mngr(p, 1);
        if (i == -1)
        {
            free(p);
            return (NULL);
        }
        else
            return (p);
    }
        
}

void    mfree(void *p)
{
    if (heap_mngr(p, 0) == -2)
        p = NULL;
}
