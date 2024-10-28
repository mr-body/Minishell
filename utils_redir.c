#include "minishell.h"

int is_redir(char *str)
{
    if (ft_strchr(str, '>>'))
        return (R_APPEND_O)
    else if (ft_strchr(str, '<<'))
        return (R_APPEND_I)
    else if (ft_strchr(str, '>'))
        return (R_TRUNC_O)
    else if (ft_strchr(str, '<'))
        return (R_TRUNC_I);
    return (0);
}