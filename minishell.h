#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_minishell
{
	/* data */
}		t_minishell;

# define String char *

# define VERDE "\033[0;32m"
# define AMARELO "\033[0;33m"
# define VERMELHO "\033[0;31m"
# define AZUL "\033[0;34m"
# define RESET "\033[0m"
# define CLEAR "\033[H\033[2J"

void	ft_putstr(char *s);
void	header(void);
void	command(void);

# define CONCAT_STRINGS(a, b) a##b

#endif