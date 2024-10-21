/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:24:38 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/21 12:43:58 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcat(char *s1, char *s2, int c)
{
	size_t	len1;
	size_t	len2;
	char	*new;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(len1 + len2 + 2);
	if (!new)
		return (NULL);
	ft_memcpy(new, s1, len1);
	new[len1] = (char)c;
	ft_memcpy(new + len1 + 1, s2, len2);
	new[len1 + len2 + 1] = '\0';
	return (new);
}

char	*expand_env_var(char *arg, char *tmp)
{
	char	single_char[2];
	int		j;
	int		k;
	char	*old_tmp;
	char	*env_var_value;
	char	*env_var_name;

	j = 0;
	while (arg[j])
	{
		if (arg[j] == '$')
		{
			j++;
			k = j;
			while (arg[k] && (ft_isalnum(arg[k]) || arg[k] == '_'))
				k++;
			env_var_name = ft_substr(arg, j, k - j);
			if (!env_var_name)
			{
				free(tmp);
				return (NULL);
			}
			env_var_value = getenv(env_var_name);
			if (env_var_value)
			{
				old_tmp = tmp;
				tmp = ft_strjoin(tmp, env_var_value);
				free(old_tmp);
			}
			free(env_var_name);
			j = k;
		}
		else
		{
			single_char[0] = arg[j];
			single_char[1] = '\0';
			old_tmp = tmp;
			tmp = ft_strjoin(tmp, single_char);
			free(old_tmp);
			j++;
		}
	}
	if ((ft_strchr(tmp, '\"')) || (ft_strchr(tmp, '\'')))
	{
		old_tmp = handle_quotes(tmp);
		if (!old_tmp)
		{
			free(tmp);
			return (NULL);
		}
		else
		{
			free(tmp);
			return (old_tmp);
		}
	}
	return(tmp);
}

char	**ft_extended(char **data)
{
	int		i;
	char	**new_data;
	char	*arg;
	char	*tmp;

	new_data = malloc(sizeof(char *) * (ft_matriz_len(data) + 1));
	ft_memset(new_data, 0, sizeof(char *) * (ft_matriz_len(data) + 1));
	if (!new_data)
		return (NULL);
	i = -1;
	while (data[++i])
	{
		arg = data[i];
		tmp = ft_strdup("");
		if (!tmp)
		{
			new_data = ft_free_matriz(new_data);
			return (NULL);
		}
		tmp = expand_env_var(arg, tmp);
		if (!tmp)
		{
			ft_free_matriz(new_data);
			return (NULL);
		}
		new_data[i] = tmp;
	}
	new_data[i] = NULL;
	return (new_data);
}

char	**ft_adjust_data(char **data)
{
	int		i;
	int		j;
	char	**new_data;
	char	*temp;

	i = -1;
	j = 0;
	new_data = malloc(sizeof(char *) * (ft_matriz_len(data) + 1));
	ft_memset(new_data, 0, sizeof(char *) * (ft_matriz_len(data) + 1));
	while (data[++i])
	{
		if (data[i][0] == '\"' && data[i][ft_strlen(data[i]) - 1] == '\"'
			&& ft_strlen(data[i]) > 1)
		{
			new_data[j++] = ft_strdup(data[i]);
		}
		else if (data[i][0] == '\"')
		{
			new_data[j] = ft_strdup(data[i]);
			while (data[i + 1] && data[i + 1][ft_strlen(data[i + 1])
				- 1] != '\"')
			{
				temp = ft_strcat(new_data[j], data[++i], ' ');
				free(new_data[j]);
				new_data[j] = temp;
				if (!new_data[j])
				{
					ft_free_matriz(new_data);
					return (NULL);
				}
			}
			if (data[i + 1])
			{
				temp = ft_strcat(new_data[j], data[++i], ' ');
				free(new_data[j]);
				new_data[j] = temp;
				if (!new_data[j])
				{
					new_data = ft_free_matriz(new_data);
					return (NULL);
				}
			}
			j++;
		}
		else
			new_data[j++] = ft_strdup(data[i]);
	}
	new_data[j] = NULL;
	return (new_data);
}

char	**net_args(char *prompt)
{
	char	**raw_data;
	char	**net_data;
	char	**data;

	raw_data = ft_split(prompt, ' ');
	net_data = ft_adjust_data(raw_data);
	ft_free_matriz(raw_data);
	data = ft_extended(net_data);
	ft_free_matriz(net_data);
	if (!data)
	{
		ft_print_syntax_error();
		ft_free_matriz(data);
		return (NULL);
	}
	return (data);
}
