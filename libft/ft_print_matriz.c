#include "libft.h"

void    ft_print_matriz(char **matriz)
{
    int     i;

    i = -1;
    while (matriz[++i])
        ft_putendl_fd(matriz[i], 1);
}