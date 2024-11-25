/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:46:29 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/22 15:18:02 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_sintax
{
	int	i;
	int	state;
	int	in_quotes;
}		t_sintax;

typedef struct s_quotes
{
	int		len;
	char	*output;
	char	current_quote;
	int		read_pos;
	int		write_pos;
}			t_quotes;

typedef struct s_utils_redir
{
	int		data_idx;
	int		is_quote;
	int		is_redirect;
	char	*current_arg;
	int		index;
}			t_utils_redir;

typedef struct s_split_redir_cmd
{
	int		data_idx;
	int		in_quotes;
	int		is_redirect;
	char	*current_arg;
	int		i;
}			t_split_redir_cmd;

typedef struct redirect
{
	int		fd[2];
	char	*tmp;
	char	*delimiter;
	char	*l;
	char	*temp_file;
	int		temp_fd;
	char	*line;
	int		type;
	int		fd_in;
}			t_redirect;

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
	int		expand;
	int		braces;
}			t_vars;

typedef struct s_minishell
{
	char	*readline;
	int		heredoc;
	char	*command;
	char	**verify_syntax;
	char	*redirect_command;
	t_data	*raw_args;
	t_data	*args;
	int		fd;
	int		gkomba;
	int		ms;
	int		waalexan;
	int		last;
	int		fd_type;
	int		*pipe_fds;
	int		exit_status;
	int		is_redir;
	int		is_stdin;
	int		redir;
	int		status;
	int		process_out;
	int		not_flag;
	char	*data[MAX_ARGS];
	int		pid_child;
}			t_minishell;

#endif
