#include "libft.h"

char	**ft_matdup(char **mat)
{
	char	**temp;
	size_t	i;

	if (!mat)
		return (NULL);
	i = 0;
	while (mat[i])
		i++;
	temp = ft_calloc(i + 1, sizeof (char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (mat[i])
	{
		temp[i] = ft_strdup (mat[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}