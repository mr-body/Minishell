#include "minishell.h"

void	ft_print_command_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	ft_print_syntax_error(void)
{
	ft_putendl_fd("minishell: syntax error: quote", 2);
}