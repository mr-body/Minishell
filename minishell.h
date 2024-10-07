#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <wait.h>
# include "libft/libft.h"

typedef struct s_minishell
{
	char *dir;
}		t_minishell;

# define String char *

# define VERDE "\033[0;32m"
# define AMARELO "\033[0;33m"
# define VERMELHO "\033[0;31m"
# define AZUL "\033[0;34m"
# define RESET "\033[0m"
# define CLEAR "\033[H\033[2J"

void	header(void);
void	command(t_minishell *minishell);


int	command_cd(char **argv, char *cmd, t_minishell *minishell);
int	command_echo(char **argv, char *cmd, char    *bin);


char *hide_parametre(const char *str, char set);
char *ft_strcat(char *s1, char *s2, int c);


# define CONCAT_STRINGS(a, b) a##b

#endif