/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkomba <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:41:57 by gkomba            #+#    #+#             */
/*   Updated: 2024/11/04 18:53:16 by gkomba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_words(const char *str, char delimiter) {
    int in_quotes = 0;
    int count = 0;
    int i = 0;

    while (str[i]) {
        if (str[i] == '"' || str[i] == '\'') {
            in_quotes = !in_quotes;
        }
        if (!in_quotes && str[i] == delimiter) {
            if (i > 0 && str[i - 1] != delimiter) {
                count++;
            }
        }
        i++;
    }
    if (i > 0 && str[i - 1] != delimiter) {
        count++;
    }

    return count;
}

char **ft_split_ms(const char *str, char delimiter) {
    if (str == NULL) {
        return NULL;
    }

    int word_count = count_words(str, delimiter);
    char **result = malloc((word_count + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    int in_quotes = 0;
    int start = -1;
    int index = 0;
    char    type_qt;

    for (int i = 0; str[i]; i++) {
        if (str[i] == '"' || str[i] == '\'') {
            in_quotes = !in_quotes;
            type_qt = str[i];
        }
        if (!in_quotes && str[i] == delimiter) {
            if (start != -1) {
                int length = i - start;
                result[index] = malloc((length + 1) * sizeof(char));
                if (result[index] == NULL) {
                    for (int j = 0; j < index; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                strncpy(result[index], str + start, length);
                result[index][length] = '\0';
                index++;
                start = -1;
            }
        } else {
            if (start == -1) {
                start = i; 
            }
        }
    }

    if (start != -1) {
        int length = strlen(str) - start;
        result[index] = malloc((length + 1) * sizeof(char));
        if (result[index] == NULL) {
            for (int j = 0; j < index; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        strcpy(result[index], str + start);
        result[index][length] = '\0';
        index++;
    }

    result[index] = NULL; // Marca o final da matriz
    return result;
}