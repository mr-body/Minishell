#include "../minishell.h"

char	*get_path(char const *str)
{
	int		len_cd;
	int		len_str;
	char	**mat;
	char	*cd;
	char	*path;
	char	*path_trimmed;

	len_str = ft_strlen(str);
	len_cd = ft_strlen("cd");
	mat = malloc(2 * sizeof(char *));
	if (!mat)
		return (NULL);
	mat[0] = ft_substr(str, 0, len_cd);
	mat[1] = ft_substr(str, len_cd + 1, (len_str - len_cd));
	return (mat[1]);
}

// implementacao do commando cd
int	command_cd(char **argv, char *cmd, t_minishell *minishell)
{
	if (argv[2])
	{
		char *temp = ft_strdup("");
		char *place = ft_strdup("");

		place = get_path(cmd);
		temp = ft_strtrim(place, "\"");
		free(place);
		place = ft_strtrim(temp, "/");
		free(temp);
		temp = hide_parametre(place, '\\');
		if (chdir(temp) != 0)
			return (perror("error"), 1);
	}
	else if (argv[1])
	{
		if (chdir(hide_parametre(argv[1], '\\')) != 0)
			return (perror("error"), 1);
	}
	else
	{
		if (chdir(getenv("HOME")) != 0)
			return (perror("error"), 1);
	}

	free(minishell->dir);
	minishell->dir = getcwd(NULL, 0);
	if (!minishell->dir)
	{
		return (perror("getcwd error"), 1);
	}
	return (0);
}