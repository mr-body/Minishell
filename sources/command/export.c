/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:18:49 by waalexan          #+#    #+#             */
/*   Updated: 2024/12/10 06:36:40 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	export_var(char **prompt)
{
	t_export_vars	var;

	ft_memset(&var, 0, sizeof(t_export_vars));
	while (prompt[++var.i])
	{
		if (check_name_var_syntax(prompt[var.i]))
			return (ft_ctrl_c(1), 1);
		var.name = ft_strndup(prompt[var.i], ft_strnlen(prompt[var.i], '='));
		var.value = ft_substr(prompt[var.i], ft_strnlen(prompt[var.i], '='),
				ft_strlen(prompt[var.i]) - ft_strnlen(prompt[var.i], '='));
		var.name_cleaned = quote_scanner(var.name);
		var.var = ft_strjoin(var.name_cleaned, var.value);
		if (is_not_new(var.name_cleaned))
		{
			if (var.value && var.value[0] != '\0')
				set_to_env(ft_get_env(var.var));
		}
		else
			set_to_env(ft_get_env(var.var));
		free(var.var);
		free(var.name);
		free(var.name_cleaned);
		free(var.value);
	}
	return (ft_ctrl_c(0), 0);
}

void	ft_print_export(t_minishell *minishell, t_export_vars	*var)
{
	ft_putstr_fd("=\"", minishell->fd);
	ft_putstr_fd(var->value, minishell->fd);
	ft_putstr_fd("\"\n", minishell->fd);
}

static int	export_print(t_minishell *minishell, char **environ)
{
	t_export_vars	var;

	ft_memset(&var, 0, sizeof(t_export_vars));
	var.sort = sort_env(environ);
	while (var.sort[var.i])
	{
		var.name = ft_strndup(var.sort[var.i],
				ft_strnlen(var.sort[var.i], '='));
		var.value = ft_substr(var.sort[var.i],
				ft_strnlen(var.sort[var.i], '=') + 1,
				ft_strlen(var.sort[var.i]) - ft_strnlen(var.sort[var.i], '='));
		ft_putstr_fd("declare -x ", minishell->fd);
		ft_putstr_fd(var.name, minishell->fd);
		if (var.value[0] != '\0')
			ft_print_export(minishell, &var);
		else
			ft_putstr_fd("\n", minishell->fd);
		free(var.name);
		free(var.value);
		var.i++;
	}
	return (ft_ctrl_c(0), 0);
}

int	command_export(char **prompt, int pipe, t_minishell *minishell)
{
	extern char	**environ;

	if (!prompt[1])
		minishell->exit_status = export_print(minishell, environ);
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
