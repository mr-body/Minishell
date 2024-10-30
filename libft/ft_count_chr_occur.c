#include "libft.h"

int	ft_count_chr_occurrency_matriz(char **mat, char chr)
{
	int	i_mtz;
	int	i_str;
	int	chr_occurrency;

	i_mtz = -1;
	chr_occurrency = 0;
	while (mat[++i_mtz])
	{
		i_str = -1;
		while (mat[i_mtz][++i_str])
		{
			if (mat[i_mtz][i_str] == chr)
				chr_occurrency += 1;
		}
	}
	return (chr_occurrency);
}

int	ft_count_chr_occurrency_str(char *str, char chr)
{
	int i;
	int chr_occurrency;

	if(!str)
		return(0);
	i = -1;
	chr_occurrency = 0;
	while (str[++i])
	{
		if (str[i] == chr)
			chr_occurrency += 1;
	}

	return (chr_occurrency);

}