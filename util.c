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

char **ft_extended(char **data)
{
    int i;
    char **new_data;
    char *tmp;
    char *env_value;
    int j;

    i = -1;
    new_data = malloc(sizeof(char *) * (ft_matriz_len(data) + 1));
    if (!new_data)
        return (NULL);
    
    while (data[++i])
    {
        tmp = NULL;
        j = 0;
        char *trimmed = ft_strtrim(data[i], "\""); // Alocação de memória
        if (!trimmed) {
            ft_free_matriz(new_data); // Liberar new_data se falhar
            return (NULL);
        }

        while (trimmed[j] && trimmed[j] != '$')
        {
            j++;
        }
        
        if (trimmed[j] == '$')
        {
            char *var_name = ft_substr(trimmed, j + 1, ft_strlen(trimmed) - j - 1);
            if (!var_name) {
                free(trimmed);
                ft_free_matriz(new_data); // Liberar new_data se falhar
                return (NULL);
            }
            env_value = getenv(var_name);
            free(var_name); // Liberar a memória alocada por ft_substr
            
            if (env_value)
            {
                char *prefix = ft_substr(trimmed, 0, j);
                if (prefix) {
                    tmp = ft_strjoin(prefix, env_value);
                    free(prefix); // Liberar prefix após uso
                }
            }
            else
            {
                tmp = ft_strdup(trimmed);
            }
        }
        else
        {
            tmp = ft_strdup(trimmed);
        }
        
        free(trimmed); // Liberar trimmed após uso
        new_data[i] = tmp;
    }
    
    new_data[i] = NULL;
    return (new_data);
}

char **ft_Adjust_data(char **data)
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
                		return NULL;
			}
			j++;
		}
		else
		{
			new_data[j++] = ft_strdup(data[i]);
		}
	}
	new_data[j] = NULL;
	return (new_data);
}

char **net_args(char *prompt)
{
    char **raw_data;
    char **net_data;
    char **data;

    raw_data = ft_split(prompt , ' ');
    net_data = ft_Adjust_data(raw_data);
    if (!net_data)
	{
		write(1, "minishell: syntax error: quote\n", 31);
        	ft_free_matriz(raw_data);
		exit(1);
	}
    data = ft_extended(net_data);
    ft_free_matriz(raw_data);
    ft_free_matriz(net_data);
    return(data);
}
