#include "libft.h"

void    ft_print_matriz(char **matriz)
{
    int     i;

    i = -1;
    while (matriz[++i])
    {
        ft_putstr_fd("[", 1);
        ft_putnbr_fd(i, 1);
        ft_putstr_fd("] ", 2);
        ft_putendl_fd(matriz[i], 1);
    }
}