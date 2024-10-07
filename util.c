#include "minishell.h"

void header(void)
{
    ft_putstr_fd(CLEAR, 1);
    ft_putstr_fd( VERDE ".88b  d88. d888888b d8b   db d888888b .d8888. db   db d88888b db      db      \n" RESET, 1);
    ft_putstr_fd( VERDE "88'YbdP`88   `88'   888o  88   `88'   88'  YP 88   88 88'     88      88      \n" RESET, 1);
    ft_putstr_fd( VERDE "88  88  88    88    88V8o 88    88    `8bo.   88ooo88 88ooooo 88      88      \n" RESET, 1);
    ft_putstr_fd( VERDE "88  88  88    88    88 V8o88    88      `Y8b. 88~~~88 88~~~~~ 88      88      \n" RESET, 1);
    ft_putstr_fd( VERDE "88  88  88   .88.   88  V888   .88.   db   8D 88   88 88.     88booo. 88booo. \n" RESET, 1);
    ft_putstr_fd( VERDE "YP  YP  YP Y888888P VP   V8P Y888888P `8888Y' YP   YP Y88888P Y88888P Y88888P \n" RESET, 1);
    ft_putstr_fd("", 1);
                                                                                                                                                         
}

char *hide_parametre(const char *str, char set) {
    int i = 0;
    int j = 0;
    char *new = malloc(ft_strlen(str) + 1);
    while (str[i]) {
        if (str[i] == set && str[i + 1] == ' ')
            i++;
        new[j++] = str[i++];
    }
    new[j] = '\0';
    return new;
}

char *ft_strcat(char *s1, char *s2, int c)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    while (s1[i])
    {
        new[i] = s1[i];
        i++;
    }  
    new[i++] = c;
    while(s2[j])
    {
        new[i] = s2[j];
        i++;
        j++;
    }
    new[i] = '\0';
    return new;
    
}