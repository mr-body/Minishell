/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waalexan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 02:13:41 by waalexan          #+#    #+#             */
/*   Updated: 2024/11/07 13:20:37 by waalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define INITIAL_ARG_COUNT 10
# define INITIAL_TEMP_SIZE 256

typedef struct increment_shell_level
{
	char	*prompt[3];
	char	*shell_level;
	char	*name;
	int		level;
}			t_increment_shell_level;

typedef struct unset
{
	int		i;
	int		j;
	int		line;
	size_t	name_len;

}			t_unset;

typedef struct heart
{
	int		i;
	int		redir;
}			t_heart;

typedef struct s_data
{
	char	**args;
	char	*types;
	int		count;
}			t_data;

typedef struct util
{
	int		i;
	int		j;
	int		k;
	int		in_word;
	char	temp[INITIAL_TEMP_SIZE];
	int		temp_index;
	int		is_quote;
	char	type_quoter;
	char	*new;
	t_data	*data;
}			t_util;

typedef struct split_ms_vars
{
	int		start;
	int		index;
	int		st;
	int		idx;
}			t_split_ms_vars;

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
	char	**verify_syntax;
	char	*redirect_command;
	t_data	*raw_args;
	t_data	*args;
	int		fd;
	int		last;
	int		fd_type;
	int		*pipe_fds;
	int		exit_status;
	int		is_redir;
	int		is_stdin;
	int		redir;
	int		status;
	char	data[MAX_WORDS][MAX_WORD_LENGTH];
}			t_minishell;

typedef struct s_redir
{
	char	*redir;
	int		redir_type;
}			t_redir;

void		header(void);

char		**ft_extended(char **data);
t_data		*net_args(char *prompt);
char		**ft_adjust_data(char **data, int *quotes);

int			shell(char **prompt, int pipe, t_minishell *minishell);
int			execute_command(t_minishell *minishell);
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
char		*shell_binary(char **prompt, char **environ, int pipe);
int			shell_builtin(char **prompt, char **environ, int pipe,
				t_minishell *minishell);
int			check_quotes(char *str, char quote_type);
char		*handle_quotes(char *tmp);
void		ft_print_syntax_error(void);
char		*expand_env_var(char *arg, char *tmp, char delimiter);
int			ft_find_little_str(char *str, char *little);
int			is_redir(char *str);
int			redir_trunc_o(t_minishell *minishell);
void		redir_append_o(t_minishell *minishell);
void		redir_trunc_in(t_minishell *minishell);
void		redir_append_in(t_minishell *minishell);
int			exec_command_pipe(t_minishell *minishell);
int			exec_command(t_minishell *minishell);
void		free_data(t_data *data);
void		ft_strtok(char *str, char *delimiter,
				char result[MAX_WORDS][MAX_WORD_LENGTH]);
int			unbalanced_quotes(char *str);
void		set_to_env(char *value);
void		increment_shell_level(t_minishell *minishell);
void		change_pwd(char *curr_pwd, t_minishell *minishell);
void		change_old_pwd(char *old_pwd, t_minishell *minishell);
void		execute_child_process_pipe(t_minishell *minishell, int i,
				int num_commands);
void		execute_child_process(t_minishell *minishell);
t_data		*ft_big_split(char *str, char delimiter);
char		**ft_split_ms(const char *str, char delimiter);
int			ft_is_only(char *str, char c);
int			verify_pipes_syntax(t_minishell *minishell);
int			verify_redir_syntax(t_minishell *minishell, char *redir_type);
int			syntax_checker(t_minishell *minishell);
int			check_if_str_is_pipe(char **matriz);
void		ft_delete_quotes(char *str);
int			check_name_var_syntax(char *var);
void		ft_in_quotes(char c, int *in_quotes);
int			extract_command(t_minishell *minishell, int *redir, int *retrn);
void		last_redir(t_minishell *minishell);
void		set_to_env(char *value);
char		**sort_env(char **environ);
char		*ft_get_env(char *var_name);
#endif