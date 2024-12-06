/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:18:49 by waalexan          #+#    #+#             */
/*   Updated: 2024/12/06 19:36:32 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	export_var(char **prompt)
{
	int		i;
	char	*var;

	i = 0;
	while (prompt[++i])
	{
		if (check_name_var_syntax(prompt[i]))
			return (ft_ctrl_c(1), 1);
		var = ft_strdup(prompt[i]);
		set_to_env(ft_get_env(var));
		free(var);
	}
	return (ft_ctrl_c(0), 0);
}

static int	export_print(void)
{
	extern char	**environ;
	int			i;
	char		*output;
	char		**sorted_env;

	i = 0;
	sorted_env = sort_env(environ);
	while (sorted_env[i])
	{
		output = ft_strjoin("declare -x ", sorted_env[i]);
		ft_putendl_fd(output, 1);
		free(output);
		i++;
	}
	return (ft_ctrl_c(0), 0);
}

int	command_export(char **prompt, int pipe, t_minishell *minishell)
{
	if (!prompt[1])
		minishell->exit_status = export_print();
	else
		minishell->exit_status = export_var(prompt);
	if (pipe)
	{
		ft_free_matriz(prompt);
		minishell->process_out = 0;
		exit(0);
	}
	return (0);
}
