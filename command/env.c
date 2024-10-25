/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:20:32 by gkomba            #+#    #+#             */
/*   Updated: 2024/10/22 11:22:32 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int command_env(char **prompt, char **env, int pipe)
{
    int i;
    char **tmp;

    tmp = ft_matdup(env); // Certificar-se que a duplicação ocorreu com sucesso
    if (!tmp)
        return (-1); // Retornar erro em caso de falha

    i = 0;
    while (tmp[i])
    {
        write(1, tmp[i], ft_strlen(tmp[i]));
        write(1, "\n", 1);
        i++;
    }

    ft_free_matriz(tmp);

    if (pipe)
    {
        ft_free_matriz(prompt);
        exit(0);
    }

    return (0);
}

