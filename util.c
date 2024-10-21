/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:24:38 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/19 18:52:28 by gkomba           ###   ########.fr       */
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

int	check_quotes(char *str, int quotes, char quote_type)
{
	int	i;
	int	quotes_s;
	int	quotes_d;

	i = 0;
	quotes_d = 0;
	quotes_s = 0;
	while (str[i])
	{
		if (str[i] == '\"' && quote_type == '\"')
			quotes_d++;
		else if (str[i] == '\'' && quote_type == '\'')
			quotes_s++;
		i++;
	}
	if (quote_type == '\'')
		return(quotes_s);
	return (quotes_d);
}

char	**ft_extended(char **data)
{
	int		i;
	char	**new_data;
	char	*tmp;
	char	*env_value;
	int		j;
	char	*var_name;
	char	*prefix;
	char	*trimmed;

	i = -1;
	new_data = malloc(sizeof(char *) * (ft_matriz_len(data) + 1));
	if (!new_data)
		return (NULL);
	while (data[++i])
	{
		tmp = NULL;
		j = 0;
		trimmed = ft_strtrim(data[i], "\"");
		if (!trimmed)
		{
			ft_free_matriz(new_data);
			return (NULL);
		}
		while (trimmed[j] && trimmed[j] != '$')
			j++;
		if (trimmed[j] == '$')
		{
			var_name = ft_substr(trimmed, j + 1, ft_strlen(trimmed) - j - 1);
			if (!var_name)
			{
				free(trimmed);
				ft_free_matriz(new_data);
				return (NULL);
			}
			env_value = getenv(var_name);
			free(var_name);
			if (env_value)
			{
				prefix = ft_substr(trimmed, 0, j);
				if (prefix)
				{
					tmp = ft_strjoin(prefix, env_value);
					free(prefix);
				}
			}
			else
				tmp = ft_strdup(trimmed);
		}
		else
		{
			tmp = ft_strdup(trimmed);
		}
		free(trimmed);
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
			if (new_data[j][ft_strlen(new_data[j]) - 1] != '\"')
			{
				new_data = ft_free_matriz(new_data);
				return (NULL);
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
	if (!net_data)
	{
		write(1, "minishell: syntax error: quote\n", 31);
		ft_free_matriz(raw_data);
		exit(1);
	}
	data = ft_extended(net_data);
	ft_free_matriz(raw_data);
	ft_free_matriz(net_data);
	return (data);
}
