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

# define VERDE "\033[0;32m"
# define AMARELO "\033[0;33m"
# define VERMELHO "\033[0;31m"
# define AZUL "\033[0;34m"
# define RESET "\033[0m"
# define CLEAR "\033[H\033[2J"

void	header(void);

char **ft_extended(char **data);
char **net_args(char *str);
char **ft_adjust_data(char **data);

int sheel(char **prompt);
void execute_command(char *prompt);

int command_cd(char **prompt);
int command_exit(char **prompt);
int command_echo(char **prompt);
int command_env(char **prompt, char **environ);
int command_pwd(char **prompt);
int command_unset(char **prompt);

char *ft_strcat(char *s1, char *s2, int c);

#endif