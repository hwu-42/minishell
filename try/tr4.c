#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char    *revere_string(char *s)
{
    char    *re;
    int     n;

    n = strlen(s);
    re = malloc(n + 1);
    re[n--] = 0;
    while (n >= 0)
    {
        re[n] = *s++;
        n--;
    }
    return (re);
}

int main(void)
{
    printf("%s\n", revere_string("asdf"));
}