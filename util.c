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

int ft_count_chr(char *str, char set) {
    int i = 0;
    while (*str) {
        if (*str == set)
            i++;
        str++;
    }
    return i;
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

char **ft_adjust_data(char **data) {
    int i = 0, j = 0;
    int data_len = ft_matriz_len(data); // Get the length of the input data
    char **new_data = malloc(sizeof(char *) * (data_len + 1)); // +1 for the NULL terminator
    char *tmp = NULL;

    if (!new_data) return NULL; // Check if allocation was successful

    while (data[i]) {
        if (ft_count_chr(data[i], '\"') % 2 == 0) {
            // If quotes are balanced, add the complete string
            new_data[j++] = data[i];
        } else {
            // Handle unbalanced quotes
            tmp = strdup(data[i]); // Duplicate the current string
            i++;
            while (data[i] && ft_count_chr(tmp, '\"') % 2 != 0) {
                char *new_tmp = ft_strcat(tmp, data[i], ' '); // Concatenate strings
                free(tmp); // Free the previous tmp
                tmp = new_tmp; // Update tmp
                i++;
            }

            if (ft_count_chr(tmp, '\"') % 2 != 0) {
                printf("Error: unbalanced quotes in '%s'\n", tmp);
                free(tmp); // Free tmp on error
                ft_free_matriz(new_data); // Free new_data on error
                return NULL;
            }
            new_data[j++] = tmp; // Add the concatenated result
        }
        i++;
    }
    new_data[j] = NULL; // Null-terminate the new array

    return new_data;
}


char	**net_args(const char *prompt)
{
	char	**raw_data;
	char	**net_data;
	char	**data;

	raw_data = ft_split(prompt, ' ');
	net_data = ft_adjust_data(raw_data);
	data = ft_extended(net_data);
	ft_free_matriz(net_data);
	if (!data)
	{
		ft_print_syntax_error();
		ft_free_matriz(data);
		return (NULL);
	}

	int i = -1;
	while(data[++i])
	{
		write(1, "\n", 1);
		ft_putstr_fd(data[i], 1);
	}

	return (data);
}
