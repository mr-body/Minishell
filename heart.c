/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heart.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:19:40 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/21 16:19:28 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*funcao que executa os comandos simples*/
void	exec_command(t_minishell *minishell)
{
	int		exit_status;
	pid_t	pid;

	minishell->args = net_args(minishell->command);
	if (!minishell->args)
	{
		ft_free_matriz(minishell->args);
		return ;
	}
	if (!minishell->args[0])
		return ;
	if (!is_builtin(minishell->args[0]))
	{
		pid = fork();
		if (pid < 0)
			perror("fork error: ");
		else if (pid == 0)
		{
			if(minishell->fd_type == 0 )
				dup2(minishell->fd, STDOUT_FILENO);
			else
				dup2(minishell->fd, STDIN_FILENO);
			if (shell(minishell->args, 0, minishell) == -1)
			{
				ft_print_command_error(minishell->args[0]);
				exit(EXIT_FAILURE);
			}
			close(minishell->fd);
		}
		else
			waitpid(pid, &minishell->exit_status, 0);
	}
	else
	{
		if (shell(minishell->args, 0, minishell) == -1)
			ft_print_command_error(minishell->args[0]);
	}
	ft_free_matriz(minishell->args);
}

/*funcao que executa os comandos quando tem pipes*/
void	exec_command_pipe(t_minishell *minishell)
{
	int		num_commands;
	int		i;
	pid_t	pid;

	minishell->raw_args = ft_split(minishell->command, '|');
	num_commands = ft_matriz_len(minishell->raw_args);
	minishell->pipe_fds = (int *)malloc(sizeof(int) * (2 * num_commands - 1));
	open_fds(minishell, num_commands);
	i = -1;
	while (++i < num_commands)
	{
		minishell->args = net_args(minishell->raw_args[i]);
		if (!minishell->args)
		{
			ft_exit_process(minishell, num_commands);
			return ;
		}
		if (!minishell->args)
			return ;
		pid = fork();
		if (pid == 0)
		{
			if(minishell->fd_type == 0 )
				dup2(minishell->fd, STDOUT_FILENO);
			else
				dup2(minishell->fd, STDIN_FILENO);
			if (i < num_commands - 1)
				dup2(minishell->pipe_fds[i * 2 + 1], STDOUT_FILENO);
			if (i > 0)
				dup2(minishell->pipe_fds[(i - 1) * 2], STDIN_FILENO);
			close_fds(minishell, num_commands);
			if (shell(minishell->args, 1, minishell) == -1)
			{
				perror("error: ");
				exit(1);
			}
			close(minishell->fd);
		}
		else if (pid < 0)
			perror("fork error: ");
		ft_free_matriz(minishell->args);
	}
	ft_exit_process(minishell, num_commands);
}

/*funcao que chama as funcao que vao exeutar os comandos*/
void	execute_command(t_minishell *minishell)
{
	// echo "como vc este" | wc -l > text.txt > header.txt
	// [0] echo "como vc este" | wc -l
	// [1] text.txt
	// [2] header.txt

	// echo teste > text > etxv >  tevxz > 6ftx

	int redir;
	int i = 0;
	char **data;
	int fd;

	minishell->fd = 1;

    redir = is_redir(minishell->readline);
	
	if (redir == R_TRUNC_O)
	{

		data = ft_strtok(minishell->readline, ">");
		minishell->command = data[0];
		minishell->fd_type = 0;

		while(++i <  (ft_matriz_len(data) - 1))
		{
			fd = open(data[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(fd);
		}
		minishell->fd = open(ft_strtrim(data[ft_matriz_len(data) - 1],  " "), O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (strchr(minishell->command, '|'))
			exec_command_pipe(minishell);
		else
			exec_command(minishell);
	}
	else if(redir == R_APPEND_O)
	{
		data = ft_strtok(minishell->readline, ">>");
		minishell->command = data[0];
		minishell->fd_type = 0;

		while(++i <  (ft_matriz_len(data) - 1))
		{
			fd = open(data[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
			close(fd);
		}
		minishell->fd = open(ft_strtrim(data[ft_matriz_len(data) - 1],  " "), O_WRONLY | O_CREAT | O_APPEND, 0644);

		if (strchr(minishell->command, '|'))
			exec_command_pipe(minishell);
		else
			exec_command(minishell);
	}
	else if(redir == R_TRUNC_I)
	{
		data = ft_strtok(minishell->readline, "<");
		minishell->command = data[0];
		minishell->fd_type = 1;

		minishell->fd = open(ft_strtrim(data[ft_matriz_len(data) - 1],  " "), O_RDONLY);

		if (strchr(minishell->command, '|'))
			exec_command_pipe(minishell);
		else
			exec_command(minishell);
	}
	else if(redir == R_APPEND_I)
	{
		data = ft_strtok(minishell->readline, "<<");
		minishell->command = data[0];
		minishell->fd_type = 1;

		char *delimiter = ft_strtrim(data[ft_matriz_len(data) - 1], " ");

		// Create a temporary file for the here-document
		char *temp_file = "/tmp/heredoc.tmp";  // Ensure to handle file naming properly in production
		int temp_fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		char *line = NULL;

		// Read lines from stdin until the delimiter
		while (1)
		{
			line = readline("> ");

			// Check for the delimiter
			if (strcmp(line, delimiter) == 0)
				break;
			
			write(temp_fd, line, strlen(line));
			write(temp_fd, "\n", 1);
		}

		free(line);
		close(temp_fd);

		// Now open the temporary file for reading
		minishell->fd = open(temp_file, O_RDONLY);
		if (minishell->fd < 0)
		{
			perror("Could not open temp file for reading");
			return;
		}

		if (strchr(minishell->command, '|'))
			exec_command_pipe(minishell);
		else
			exec_command(minishell);

		// Clean up: remove the temporary file after use
		unlink(temp_file);
	}
    else
    {
		minishell->command = minishell->readline;
		if (strchr(minishell->command, '|'))
			exec_command_pipe(minishell);
		else
			exec_command(minishell);
	}
}
