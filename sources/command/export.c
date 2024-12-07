/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:18:49 by waalexan          #+#    #+#             */
/*   Updated: 2024/12/07 19:02:53 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	export_var(char **prompt)
{
	int		i;
	char	*var;
	char	*name;
	char	*name_cleaned;
	char	*value;

	i = 0;
	while (prompt[++i])
	{
		if (check_name_var_syntax(prompt[i]))
			return (ft_ctrl_c(1), 1);
		name = ft_strndup(prompt[i], ft_strnlen(prompt[i], '='));
		value = ft_substr(prompt[i], ft_strnlen(prompt[i], '='),
				ft_strlen(prompt[i]) - ft_strnlen(prompt[i], '='));
		name_cleaned = quote_scanner(name);
		var = ft_strjoin(name_cleaned, value);
		set_to_env(ft_get_env(var));
		free(var);
		free(name);
		free(name_cleaned);
		free(value);
	}
	return (ft_ctrl_c(0), 0);
}

static int	export_print(t_minishell *minishell)
{
	extern char	**environ;
	int			i;
	char		*name;
	char		*value;
	char		**sorted_env;

	i = 0;
	sorted_env = sort_env(environ);
	while (sorted_env[i])
	{
		name = ft_strndup(sorted_env[i], ft_strnlen(sorted_env[i], '='));
		value = ft_substr(sorted_env[i], ft_strnlen(sorted_env[i], '=') + 1,
				ft_strlen(sorted_env[i]) - ft_strnlen(sorted_env[i], '='));
		ft_putstr_fd("declare -x ", minishell->fd);
		ft_putstr_fd(name, minishell->fd);
		ft_putstr_fd("=\"", minishell->fd);
		ft_putstr_fd(value, minishell->fd);
		ft_putstr_fd("\"\n", minishell->fd);
		free(name);
		free(value);
		i++;
	}
	return (ft_ctrl_c(0), 0);
}

int	command_export(char **prompt, int pipe, t_minishell *minishell)
{
	if (!prompt[1])
		minishell->exit_status = export_print(minishell);
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
