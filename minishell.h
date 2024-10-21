#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <wait.h>

# define VERDE "\033[0;32m"
# define AMARELO "\033[0;33m"
# define VERMELHO "\033[0;31m"
# define AZUL "\033[0;34m"
# define RESET "\033[0m"
# define CLEAR "\033[H\033[2J"

typedef struct s_minishell
{
	char	*readline;
	char	**raw_args;
	char	**args;
	int		*pipe_fds;
	int		exit_status;
}			t_minishell;

void		header(void);

char		**ft_extended(char **data);
char		**net_args(char *str);
char		**ft_adjust_data(char **data);

int			shell(char **prompt, int pipe);
void		execute_command(t_minishell *minishell);

int			command_cd(char **prompt);
int			command_exit(char **prompt);
int			command_echo(char **prompt, int pipe);
int			command_env(char **prompt, char **environ, int pipe);
int			command_pwd(char **prompt, int pipe);
int			command_unset(char **prompt);
int			command_export(char **prompt, int pipe);

char		*ft_strcat(char *s1, char *s2, int c);

/*new funtions*/
void		ft_exit_process(t_minishell *minishell, int nbr_cmds);
void		close_fds(t_minishell *minishell, int nbr_cmds);
void		open_fds(t_minishell *minishell, int nbr_cmds);
void		ft_print_command_error(char *cmd);
int			is_builtin(char *cmd);
char		*shell_binary(char **prompt, char **environ);
int			shell_builtin(char **prompt, char **environ, int pipe);
int			check_quotes(char *str, char quote_type);
char		*handle_quotes(char *tmp);
void	ft_print_syntax_error(void);
#endif
