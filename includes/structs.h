/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:46:29 by gkomba            #+#    #+#             */
/*   Updated: 2024/12/10 06:51:20 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_export_vars
{
	int		i;
	char	*var;
	char	*name;
	char	*name_cleaned;
	char	*value;
	char	**sort;
}			t_export_vars;

typedef struct s_epur_vars
{
	int		i;
	int		j;
	int		in_d_quotes;
	int		in_s_quotes;
	int		prev_space;
}			t_epur_vars;

typedef struct s_local_data
{
	int		i;
	int		fd;
	char	*file;
}			t_local_data;

typedef struct s_pipe_data
{
	int		num_commands;
	int		fd[2];
	int		prev_fd;
	int		in_fd;
	int		out_fd;
	int		i;
	pid_t	pid;
}			t_pipe_data;

typedef struct s_sintax
{
	int		i;
	int		state;
	int		in_s_quotes;
	int		in_d_quotes;
}			t_sintax;

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
	int		in_d_quotes;
	int		in_s_quotes;
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
	char	*file;
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
	int		k;
	int		in_word;
	char	*old_tmp;
	char	*env_var_value;
	char	*env_var_name;
	int		expand;
	int		braces;
	bool	in_s_quotes;
	bool	in_d_quotes;
	bool	allow_expand;
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
	int		exit;
	int		process_out;
	int		not_flag;
	char	*data[MAX_ARGS];
	int		pid_child;
	char	*temp;
	char	**check_data;
}			t_minishell;

#endif
