#include "minishell.h"

char	*ft_strcat(char *s1, char *s2, int c)
{
	size_t	len1;
	size_t	len2;
	char	*new;
	size_t	i;
    size_t  j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(len1 + len2 + 2);
	if (new == NULL)
		return (NULL);
	i = -1;
	while (++i < len1)
		new[i] = s1[i];
	new[len1] = (char)c;
	i = len1 + 1;
	j = -1;
	while (++j < len2)
		new[i++] = s2[j];
	new[i] = '\0';
	return (new);
}

char	**ft_adjust_data(char **data)
{
	int		i;
	int		j;
	char	**new_data;

	i = -1;
	j = 0;
	new_data = (char **)malloc(sizeof(char *) * (ft_matriz_len(data) + 1));
	while (data[++i])
	{
		if (data[i][0] == '\"' && data[i][ft_strlen(data[i]) - 1] == '\"'
			&& ft_strlen(data[i]) > 1)
			new_data[j++] = ft_strdup(data[i]);
		else if (data[i][0] == '\"')
		{
			new_data[j] = ft_strdup(data[i]);
			while (data[i + 1] && data[i + 1][ft_strlen(data[i + 1])
				- 1] != '\"')
				new_data[j] = ft_strcat(new_data[j], data[++i], ' ');
			if (data[i + 1])
				new_data[j] = ft_strcat(new_data[j], data[++i], ' ');
			if (new_data[j][ft_strlen(new_data[j]) - 1] != '\"')
				return (NULL);
			j++;
		}
		else if (data[i][ft_strlen(data[i]) - 1] == '\"')
			return (NULL);
		else
			new_data[j++] = ft_strdup(data[i]);
	}
	return (new_data[j] = '\0', new_data);
}

char	**ft_extended(char **data)
{
	int		i;
	int		j;
	char	**new_data;
	char	*tmp;
	char	*env_value;

	i = -1;
	new_data = (char **)malloc(sizeof(char *) * (ft_matriz_len(data) + 1));
	while (data[++i])
	{
		j = 0;
		tmp = NULL;
		data[i] = ft_strtrim(data[i], "\"");
		while (data[i][j] && data[i][j] != '$')
			j++;
		if (data[i][j] == '$')
		{
			env_value = getenv(ft_substr(data[i], j + 1, ft_strlen(data[i]) - j
						- 1));
			if (env_value)
				tmp = ft_strjoin(ft_substr(data[i], 0, j), env_value);
			else
				tmp = ft_strdup(data[i]);
		}
		else
			tmp = ft_strdup(data[i]);
		new_data[i] = tmp;
	}
	new_data[i] = '\0';
	return (new_data);
}

char	**net_args(char *str)
{
	char **raw_data;
	char **net_data;
	char **data;

	raw_data = ft_split(str, ' ');
	net_data = ft_adjust_data(raw_data);
	if (net_data == NULL)
	{
		write(1, "minishell: syntax error: quote\n", 31);
		exit(1);
	}
	else
	{
		data = ft_extended(net_data);
	}

	for (int i = 0; raw_data[i]; i++)
		free(raw_data[i]);
	free(raw_data);
	return (data);
}