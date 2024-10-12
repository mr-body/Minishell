#include "minishell.h"

void header(void)
{
    ft_putstr_fd(CLEAR, 1);
    // ft_putstr_fd( VERDE ".88b  d88. d888888b d8b   db d888888b .d8888. db   db d88888b db      db      \n" RESET, 1);
    // ft_putstr_fd( VERDE "88'YbdP`88   `88'   888o  88   `88'   88'  YP 88   88 88'     88      88      \n" RESET, 1);
    // ft_putstr_fd( VERDE "88  88  88    88    88V8o 88    88    `8bo.   88ooo88 88ooooo 88      88      \n" RESET, 1);
    // ft_putstr_fd( VERDE "88  88  88    88    88 V8o88    88      `Y8b. 88~~~88 88~~~~~ 88      88      \n" RESET, 1);
    // ft_putstr_fd( VERDE "88  88  88   .88.   88  V888   .88.   db   8D 88   88 88.     88booo. 88booo. \n" RESET, 1);
    // ft_putstr_fd( VERDE "YP  YP  YP Y888888P VP   V8P Y888888P `8888Y' YP   YP Y88888P Y88888P Y88888P \n" RESET, 1);
    // ft_putstr_fd("", 1);
                                                                                                                                                         
}

char *ft_strcat(char *s1, char *s2, int c)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    while (s1[i])
    {
        new[i] = s1[i];
        i++;
    }  
    new[i++] = c;
    while(s2[j])
    {
        new[i] = s2[j];
        i++;
        j++;
    }
    new[i] = '\0';
    return new;
}

char **ft_adjust_data(char **data)
{
    int i;
    int j;
    char **new_data;

    i = -1;
    j = 0;
    new_data = (char **)malloc(sizeof(char *) * (ft_matriz_len(data) + 1));
    while(data[++i])
    {
        if(data[i][0] == '\"' && data[i][ft_strlen(data[i]) - 1] == '\"' && ft_strlen(data[i]) > 1)
            new_data[j++] = ft_strdup(data[i]);
        else if(data[i][0] == '\"')
        {
            new_data[j] = ft_strdup(data[i]);
            while(data[i+1] && data[i+1][ft_strlen(data[i + 1]) - 1] != '\"')
               new_data[j] = ft_strcat(new_data[j], data[++i], ' ');
            if (data[i+1])
                new_data[j] = ft_strcat(new_data[j], data[++i], ' ');
            if (new_data[j][ft_strlen(new_data[j]) - 1] != '\"')
                return (NULL);
            j++;
        }
        else if(data[i][ft_strlen(data[i]) - 1] == '\"')
            return (NULL);
        else
            new_data[j++] = ft_strdup(data[i]);
    }
    return (new_data[j] = '\0', new_data);
}

char **ft_extended(char **data)
{
    int i;
    int j;
    char **new_data;
    char *tmp;

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
            char *env_value = getenv(ft_substr(data[i], j + 1, ft_strlen(data[i]) - j - 1));
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
    return new_data;
}

char **net_args(char *str)
{
    char **raw_data;
    char **net_data;
    char **data;

    raw_data = ft_split(str, ' ');
    net_data = ft_adjust_data(raw_data);
    if(net_data == NULL)
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

    return data;
}