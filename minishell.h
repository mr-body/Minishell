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

typedef struct vars
{
	int		i;
	int		j;
	int		k;
	int		in_word;
	char	*old_tmp;
	char	*env_var_value;
	char	*env_var_name;
}			t_vars;

typedef struct s_minishell
{
	char	*readline;
	char	*command;
	char	**raw_args;
	char	**args;
	int		fd;
	int		fd_type;
	int		*pipe_fds;
	int		exit_status;
	int		redir;
	char	data[MAX_WORDS][MAX_WORD_LENGTH];
}			t_minishell;

typedef struct s_redir
{
	char	*redir;
	int		redir_type;
}			t_redir;

void		header(void);

char		**ft_extended(char **data);
char		**net_args(char *prompt);
char		**ft_adjust_data(char **data);

int			shell(char **prompt, int pipe, t_minishell *minishell);
void		execute_command(t_minishell *minishell);
int			command_cd(char **prompt, t_minishell *minishell);
int			command_exit(char **prompt, t_minishell *minishell);
int			command_echo(char **prompt, int pipe, t_minishell *minishell);
int			command_env(char **prompt, char **environ, int pipe,
				t_minishell *minishell);
int			command_pwd(char **prompt, int pipe, t_minishell *minishell);
int			command_unset(char **prompt, int pipe, t_minishell *minishell);
int			command_export(char **prompt, int pipe, t_minishell *minishell);

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
int			is_redirin(char *str);
void		redir_trunc_o(t_minishell *minishell);
void		redir_append_o(t_minishell *minishell);
void		redir_trunc_in(t_minishell *minishell);
void		redir_append_in(t_minishell *minishell);
void		exec_command_pipe(t_minishell *minishell);
void		exec_command(t_minishell *minishell);
void		ft_strtok(char *str, char *delimiter,
				char result[MAX_WORDS][MAX_WORD_LENGTH]);
char	*trim_quotes(char *tmp);
int		unbalanced_quotes(char *str);
void	set_to_env(char *value);
void	increment_shell_level(t_minishell *minishell);
void	change_pwd(char *curr_pwd, t_minishell *minishell);
void	change_old_pwd(char *old_pwd, t_minishell *minishell);
#endif