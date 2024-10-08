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

int	command_cd(char **argv, char *cmd, t_minishell *minishell)
{
	char *target_dir = NULL;
	char *place = NULL;

	if (argv[1])
	{
		if (ft_strncmp(argv[1], "--", ft_strlen(argv[1])) == 0
			&& ft_strlen(argv[1]) == 2)
		{
			target_dir = getenv("HOME");
		}
		else if (ft_strncmp(argv[1], "-", ft_strlen(argv[1])) == 0
			&& ft_strlen(argv[1]) == 1)
		{
			char *current_dir = getcwd(NULL, 0);
			char *home = getenv("HOME");

			if (ft_strncmp(current_dir, home, ft_strlen(home)) == 0)
				target_dir = home;
			else
			{
				char *parent_dir = current_dir;
				int i = ft_strlen(current_dir);
				while (i > 0 && current_dir[i - 1] != '/')
					i--;
				target_dir = ft_substr(parent_dir, 0, i);
			}
			free(current_dir); 
		}

		else
		{
			if ((argv[1][0] == '\"' || argv[1][0] == '\'')
					|| argv[1][strlen(argv[1]) - 1] == '\\')
			{
				place = get_path(cmd);
				if (place)
				{
					place = ft_strtrim(place, "\"'");
					target_dir = hide_parametre(place, '\\');
					free(place);
				}
			}
			else
			{
				target_dir = hide_parametre(argv[1], '\\');
			}

			// Handle tilde expansion
			if (target_dir && target_dir[0] == '~')
			{
				char *home = getenv("HOME");
				if (home)
				{
					char *new_target = ft_strjoin(home, target_dir + 1);
					free(target_dir); // free previous allocation
					target_dir = new_target;
				}
			}
		}

		if (target_dir)
		{
			if (chdir(target_dir) != 0)
			{
				return (1);
			}
			// Free only if target_dir was dynamically allocated
			if (target_dir && target_dir != getenv("HOME")
				&& target_dir != NULL)
			{
				free(target_dir);
			}
		}
	}
	else
	{
		target_dir = getenv("HOME");
		if (target_dir && chdir(target_dir) != 0)
		{
			return (1);
		}
	}

	// Update the current directory in the minishell struct
	free(minishell->dir);
	minishell->dir = getcwd(NULL, 0);
	if (!minishell->dir)
	{
		perror("getcwd error");
		return (1);
	}

	return (0);
}