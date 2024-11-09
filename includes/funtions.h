/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funtions.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:53:12 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/09 14:20:18 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNTIONS_H
# define FUNTIONS_H

t_data	*net_args(char *prompt);
t_data	*ft_big_split(char *str, char delimiter);
char	**ft_extended(char **data);
char	**ft_adjust_data(char **data, int *quotes);
char	*handle_quotes(char *tmp);
char	*expand_env_var(char *arg, char *tmp, char delimiter);
char	*ft_get_env(char *var_name);
char	**sort_env(char **environ);
char	*shell_binary(char **prompt);
char	**ft_split_ms(const char *str, char delimiter);
int		shell(char **prompt, int pipe, t_minishell *minishell);
int		execute_command(t_minishell *minishell);
int		command_cd(char **prompt, t_minishell *minishell);
int		command_exit(char **prompt, t_minishell *minishell);
int		command_echo(char **prompt, int pipe, t_minishell *minishell);
int		command_env(char **prompt, char **environ, int pipe,
			t_minishell *minishell);
int		command_pwd(char **prompt, int pipe, t_minishell *minishell);
int		command_unset(char **prompt, int pipe);
int		command_export(char **prompt, int pipe, t_minishell *minishell);
int		is_builtin(char *cmd);
int		shell_builtin(char **prompt, char **environ, int pipe,
			t_minishell *minishell);
int		check_quotes(char *str, char quote_type);
int		ft_find_little_str(char *str, char *little);
int		is_redir(char *str);
int		redir_trunc_o(t_minishell *minishell);
int		exec_command_pipe(t_minishell *minishell);
int		exec_command(t_minishell *minishell);
int		unbalanced_quotes(char *str);
int		ft_is_only(char *str, char c);
int		verify_pipes_syntax(t_minishell *minishell);
int		verify_redir_syntax(t_minishell *minishell, char *redir_type);
int		syntax_checker(t_minishell *minishell);
int		check_if_str_is_pipe(char **matriz);
int		check_name_var_syntax(char *var);
int		extract_command(t_minishell *minishell, int *redir, int *retrn);
int		check_invalid_character(char *arg);
int		return_redir_type(char curr_c, char next_c);
int		check_redir_one(t_minishell *minishell, int i, char *redir_type);
int		check_redir_two(t_minishell *minishell, int i, char *redir_type);
void	ft_print_syntax_error(void);
void	ft_exit_process(t_minishell *minishell, int nbr_cmds);
void	close_fds(t_minishell *minishell, int nbr_cmds);
void	open_fds(t_minishell *minishell, int nbr_cmds);
void	ft_print_command_error(char *cmd);
void	free_data(t_data *data);
void	ft_strtok(char *str, char *delimiter,
			char result[MAX_WORDS][MAX_WORD_LENGTH]);
void	set_to_env(char *value);
void	increment_shell_level(t_minishell *minishell);
void	change_pwd(char *curr_pwd, t_minishell *minishell);
void	change_old_pwd(char *old_pwd, t_minishell *minishell);
void	execute_child_process_pipe(t_minishell *minishell, int i,
			int num_commands);
void	redir_append_o(t_minishell *minishell);
void	redir_trunc_in(t_minishell *minishell);
void	redir_append_in(t_minishell *minishell);
void	execute_child_process(t_minishell *minishell);
void	ft_delete_quotes(char *str);
void	ft_in_quotes(char c, int *in_quotes);
void	last_redir(t_minishell *minishell);
void	set_to_env(char *value);
void	invalid_char_error(char c);
void	redir_syntax_error(char *str);
void	pipe_syntax_error(char *str);

void	split_redirect_command(char *command, char **data, char delimiter);
#endif