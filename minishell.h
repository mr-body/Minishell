#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
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

# define R_APPEND_O 42
# define R_TRUNC_O 1337
# define R_APPEND_I 21
# define R_TRUNC_I 19

typedef struct s_minishell
{
	char	*readline;
	char	*command;
	char	**raw_args;
	char	**args;
	int		fd;
	int		*pipe_fds;
	int		exit_status;
	int		redir;
}			t_minishell;

void		header(void);

char		**ft_extended(char **data);
char		**net_args(char *prompt);
char		**ft_adjust_data(const char **data);

int			shell(char **prompt, int pipe, t_minishell *minishell);
void		execute_command(t_minishell *minishell);
char		**ft_strtok(char *str, char *delimiter);

int			command_cd(char **prompt, t_minishell *minishell);
int			command_exit(char **prompt, t_minishell *minishell);
int			command_echo(char **prompt, int pipe, t_minishell *minishell);
int			command_env(char **prompt, char **environ, int pipe,
				t_minishell *minishell);
int			command_pwd(char **prompt, int pipe, t_minishell *minishell);
int			command_unset(char **prompt, int pipe, t_minishell *minishell);
int			command_export(char **prompt, int pipe, t_minishell *minishell);

char		*ft_strcat(char *s1, char *s2, int c);

/*new funtions*/
void		ft_exit_process(t_minishell *minishell, int nbr_cmds);
void		close_fds(t_minishell *minishell, int nbr_cmds);
void		open_fds(t_minishell *minishell, int nbr_cmds);
void		ft_print_command_error(char *cmd);
int			is_builtin(char *cmd);
char		*shell_binary(char **prompt, char **environ);
int			shell_builtin(char **prompt, char **environ, int pipe,
				t_minishell *minishell);
int			check_quotes(char *str, char quote_type);
char		*handle_quotes(char *tmp);
void		ft_print_syntax_error(void);

char		*expand_env_var(char *arg, char *tmp);
int			ft_find_little_str(char *str, char *little);
int			is_redir(char *str);
int			is_redirout(char *str);
#endif
