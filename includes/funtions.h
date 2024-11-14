/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funtions.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:53:12 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/14 11:15:27 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNTIONS_H
# define FUNTIONS_H

t_data	*net_args(char *prompt);
t_data	*ft_big_split(char *str, char delimiter);
char	*quote_scanner(const char *input);
char	*expander(char *arg, char *tmp);
char	*ft_get_env(char *var_name);
char	**sort_env(char **environ);
char	*shell_binary(char **prompt);
char	*get_last_return(char *tmp);
char	**ft_split_ms(const char *str, char delimiter);
char	*join_single_char(char *tmp, char chr);
int		shell(char **prompt, int pipe, t_minishell *minishell);
int		execute_command(t_minishell *minishell);
int		command_cd(char **prompt, t_minishell *minishell);
int		command_echo(char **prompt, int pipe, t_minishell *minishell);
int		command_env(char **prompt, char **environ, int pipe,
			t_minishell *minishell);
int		command_pwd(char **prompt, int pipe, t_minishell *minishell);
int		command_unset(char **prompt, int pipe, t_minishell *minishell);
int		command_export(char **prompt, int pipe, t_minishell *minishell);
int		is_builtin(char *cmd);
int		shell_builtin(char **prompt, char **environ, int pipe,
			t_minishell *minishell);
int		is_redir(char *str);
int		redir_trunc_o(t_minishell *minishell);
int		exec_command_pipe(t_minishell *minishell);
int		exec_command(t_minishell *minishell);
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
int		ft_ctrl_c(int value);
int		in_quotes(t_split_redir_cmd *vars, char *command);
int		allow_expand(char *str);
int		command_exit(char **prompt, int pipe, t_minishell *minishell);
int		redir_is_not_followed_by_pipe(char **matriz);
int		redir_trunc_o_aux(t_minishell *minishell);
int		redir_append_o_aux(t_minishell *minishell);
int		redir_trunc_in_aux(t_minishell *minishell);
int		redir_append_in_aux(t_minishell *minishell, t_redirect *var);
int		validate_command(char *input);
int		validate_sintax(char *input);
int		ft_prompt(t_minishell *minishell);
int		is_new_prompt(t_minishell *minishell);
void	ft_print_syntax_error(void);
void	ft_delete_quotes_on_matriz(char **prompt);
void	ft_exit_process(t_minishell *minishell, int nbr_cmds);
void	close_fds(t_minishell *minishell, int nbr_cmds);
void	open_fds(t_minishell *minishell, int nbr_cmds);
void	ft_print_command_error(char *cmd);
void	free_data(t_data *data);
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
void	ft_in_quotes(char c, int *in_quotes);
void	last_redir(t_minishell *minishell);
void	set_to_env(char *value);
void	redir_syntax_error(char *str);
void	pipe_syntax_error(char *str);
void	last_return(t_minishell *minishell, char *str, int pid);
void	last_return_pipe(t_minishell *minishell);
void	split_redirect_command(char *command, char **data, char delimiter);
void	redir_append_in_case_one(t_minishell *minishell, t_redirect *var);
void	redir_trunc_in_case_one(t_minishell *minishell);
void	redir_trunc_o_case_one(t_minishell *minishell);
void	redir_append_o_case_one(t_minishell *minishell);
void	handing_c(int signal);
void	is_on_brace(char *arg, t_vars *var, char *str);
void	inset_at_the_heredoc(t_redirect *var);
void	quote_scanner_command(char *input);
void	ft_prompt_sms(char c);
void	clean(t_minishell *minishell);
#endif