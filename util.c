/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:24:38 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/30 15:31:35 by gkomba           ###   ########.fr       */
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
	return (tmp);
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

void	ft_strtok(char *str, char *delimiter,
		char result[MAX_WORDS][MAX_WORD_LENGTH])
{
	int	i;
	int	j;
	int	k;
	int	in_word;

	i = 0;
	j = 0;
	k = 0;
	in_word = 0;
	while (str[i])
	{
		if (strchr(delimiter, str[i]))
		{
			if (in_word)
			{
				result[j][k] = '\0';
				j++;
				k = 0;
				in_word = 0;
			}
		}
		else
		{
			if (k < MAX_WORD_LENGTH - 1)
			{
				result[j][k] = str[i];
				k++;
			}
			in_word = 1;
		}
		i++;
	}
	if (in_word)
	{
		result[j][k] = '\0';
		j++;
	}
	i = j;
	while (i < MAX_WORDS)
	{
		result[i][0] = '\0';
		i++;
	}
}

char	**ft_adjust_data(char **data)
{
	int		i = -1, j;
	char	**new;
	char	*tmp;
	char	*new_tmp;

	i = -1, j = 0;
	new = malloc(sizeof(char *) * (ft_matriz_len(data) + 1));
	tmp = NULL;
	if (!new)
		return (NULL);
	while (data[++i])
	{
		if (ft_count_chr_occurrency_str(data[i], '\"') % 2 == 0)
			new[j] = data[i];
		else
		{
			tmp = strdup(data[i]);
			if (!tmp)
				return (NULL);
			if (data[i + 1])
			{
				i++;
				while (data[i] && ft_count_chr_occurrency_str(tmp, '\"')
					% 2 != 0)
				{
					new_tmp = ft_strcat(tmp, data[i], ' ');
					free(tmp);
					tmp = new_tmp;
					if (data[i + 1] && ft_count_chr_occurrency_str(tmp, '\"')
						% 2 != 0)
						i++;
					else
						break ;
				}
			}
			if (ft_count_chr_occurrency_str(tmp, '\"') % 2 == 0)
				new[j] = tmp;
		}
		j++;
	}
	new[j] = NULL;
	return (new);
}

char	**net_args(char *prompt)
{
	char	**raw_data;
	char	**net_data;
	char	**data;

	if (ft_count_chr_occurrency_str(prompt, '\"') % 2 != 0)
	{
		printf("Error: unbalanced quotes\n");
		return (NULL);
	}
	raw_data = ft_split(prompt, ' ');
	net_data = ft_adjust_data(raw_data);
	data = ft_extended(net_data);
	return (data);
}
