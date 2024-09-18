#include "minishell.h"

void header(void)
{
    ft_putstr(CLEAR);
    ft_putstr( VERDE ".88b  d88. d888888b d8b   db d888888b .d8888. db   db d88888b db      db      \n" RESET);
    ft_putstr( VERDE "88'YbdP`88   `88'   888o  88   `88'   88'  YP 88   88 88'     88      88      \n" RESET);
    ft_putstr( VERDE "88  88  88    88    88V8o 88    88    `8bo.   88ooo88 88ooooo 88      88      \n" RESET);
    ft_putstr( VERDE "88  88  88    88    88 V8o88    88      `Y8b. 88~~~88 88~~~~~ 88      88      \n" RESET);
    ft_putstr( VERDE "88  88  88   .88.   88  V888   .88.   db   8D 88   88 88.     88booo. 88booo. \n" RESET);
    ft_putstr( VERDE "YP  YP  YP Y888888P VP   V8P Y888888P `8888Y' YP   YP Y88888P Y88888P Y88888P \n" RESET);
    ft_putstr("");
                                                                                                                                                         
}

void ft_putstr(char *s)
{
    while(*s)
	{
        write(1, s++, 1);
	}
}

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static char *ft_strncpy(char *s1, char *s2, int n)
{
	int i = -1;

	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

char	**ft_split(char *str, char chr)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int wc = 0;
	
	while (str[i])
	{
		while (str[i] && (str[i] == chr))
			i++;
		if (str[i])
			wc++;
		while (str[i] && (str[i] != chr))
			i++;
	}
	
	char **out = (char **)malloc(sizeof(char *) * (wc + 1));
	i = 0;
	
	while (str[i])
	{
		while (str[i] && (str[i] == chr))
			i++;
		j = i;
		while (str[i] && (str[i] != chr))
			i++;
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			ft_strncpy(out[k++], &str[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
}