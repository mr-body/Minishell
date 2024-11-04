#include "minishell.h"

void	ft_strtok(char *str, char *delimiter,
		char result[MAX_WORDS][MAX_WORD_LENGTH])
{
	int	i = 0, j = 0, k = 0, in_word;

	i = 0, j = 0, k = 0, in_word = 0;
	while (str[i])
	{
		if (ft_strchr(delimiter, str[i]))
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
				result[j][k++] = str[i];
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
	while (j < MAX_WORDS)
	{
		result[j++][0] = '\0';
	}
}

char	**ft_big_split(char *str)
{
	char	**args;
	char	temp[INITIAL_TEMP_SIZE];
	int		temp_index = 0, count;
	int		is_quote;
	char	type_quoter;
	char	*new;

	args = malloc(INITIAL_ARG_COUNT * sizeof(char *));
	if (!args)
		return (NULL); // Check allocation
	temp_index = 0, count = 0;
	is_quote = 0;
	type_quoter = 0;
	while (*str)
	{
		// Check for opening quote
		if (*str == '"' || *str == '\'')
		{
			if (is_quote == 0)
			{
				// Starting a quoted section
				is_quote = 1;
				type_quoter = *str;
			}
			else if (*str == type_quoter)
			{
				// Ending the quoted section
				is_quote = 0;
			}
			if (*str != type_quoter)
				temp[temp_index++] = *str;
			// Skip the quote character itself
			str++;
			continue ;
		}
		if (is_quote)
		{
			// If we are inside quotes, include the character in temp
			if (temp_index < INITIAL_TEMP_SIZE - 1)
			{
				temp[temp_index++] = *str;
			}
		}
		else if (*str == ' ')
		{
			// If we hit a space and we are not in quotes, finalize the current word
			if (temp_index > 0)
			{
				temp[temp_index] = '\0'; // Null-terminate the string
				new = expand_env_var(temp, ft_strdup(""), type_quoter);
				args[count++] = new;
				if (!args[count - 1])
					ft_free_matriz(args);
				temp_index = 0; // Reset temp index for the next word
			}
		}
		else
		{
			// Normal character, add to temp
			if (temp_index < INITIAL_TEMP_SIZE - 1)
			{
				temp[temp_index++] = *str;
			}
		}
		str++;
	}
	// Handle the last word if there's any left in temp
	if (temp_index > 0)
	{
		temp[temp_index] = '\0';
		new = expand_env_var(temp, ft_strdup(""), type_quoter);
		args[count++] = new;
		if (!args[count - 1])
			ft_free_matriz(args);
	}
	args[count] = NULL; // Null-terminate the array
	return (args);
}

void	ft_delete_first_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	ft_memmove(str, str + i, ft_strlen(str + i) + 1);
}

void	ft_check_is_have_env_var(char **data)
{
	int i;
	char	*old_tmp;
	i = 0;
	while(data[i])
	{
		if (ft_strchr(data[i], '$'))
		{
			old_tmp = data[i];
			data[i] = expand_env_var(data[i], ft_strdup(""), 0);
			free(old_tmp);
		}
		i++;
	}
}

char	**net_args(char *prompt)
{
	char **data;
	int quotes;

	quotes = 1;
	// data = ft_big_split(prompt, 32);
	data = ft_split_ms(prompt, 32);
	ft_check_is_have_env_var(data);
	//ft_print_matriz(data);
	return (data);
}