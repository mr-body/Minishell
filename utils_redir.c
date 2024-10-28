#include "minishell.h"

int is_redir(char *str)
{
    if (ft_count_chr_occurrency_str(str, '>') == 2)
        return (R_APPEND_O);
    else if (ft_count_chr_occurrency_str(str, '<') == 2)
        return (R_APPEND_I);
    else if (ft_count_chr_occurrency_str(str, '>') == 1)
        return (R_TRUNC_O);
    else if (ft_count_chr_occurrency_str(str, '<') == 1)
        return (R_TRUNC_I);
    return (0);
}

int redirect_input(t_minishell *minishell, int redir_mode)
{
    ft_putendl_fd("walter oppai", 1);
    return 0;
}

int redirect_output(t_minishell *minishell, int redir_mode)
{
    ft_putendl_fd("walter oppai", 1);
    return 0;
}


int    redirect(t_minishell *minishell)
{
    int redir;

    redir = is_redir(minishell->readline);
    if ((redir == R_APPEND_O) || (redir = R_TRUNC_O))
        redirect_output(minishell, redir);
    else if ((redir == R_APPEND_I) || (redir == R_TRUNC_I))
        redirect_input(minishell, redir);
    else
        return 0;
    return (redir);
}