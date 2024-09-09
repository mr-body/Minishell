#include "minishell.h"

void header(void)
{
    ft_putstr(CLEAR);
    ft_putstr("");
    ft_putstr( VERDE ".88b  d88. d888888b d8b   db d888888b .d8888. db   db d88888b db      db      \n" RESET);
    ft_putstr( VERDE "88'YbdP`88   `88'   888o  88   `88'   88'  YP 88   88 88'     88      88      \n" RESET);
    ft_putstr( VERDE "88  88  88    88    88V8o 88    88    `8bo.   88ooo88 88ooooo 88      88      \n" RESET);
    ft_putstr( VERDE "88  88  88    88    88 V8o88    88      `Y8b. 88~~~88 88~~~~~ 88      88      \n" RESET);
    ft_putstr( VERDE "88  88  88   .88.   88  V888   .88.   db   8D 88   88 88.     88booo. 88booo. \n" RESET);
    ft_putstr( VERDE "YP  YP  YP Y888888P VP   V8P Y888888P `8888Y' YP   YP Y88888P Y88888P Y88888P \n" RESET);
    ft_putstr("");
                                                                                                                                                         
}

void ft_putstr(char *s)
{
    while(*s)
        write(1, s++, 1);
}