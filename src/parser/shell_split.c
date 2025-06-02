/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:56:57 by haaghaja          #+#    #+#             */
/*   Updated: 2025/05/31 19:06:44 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_split_count(char *str, char sep)
{
	int		count;
	char	quote;

	count = 0;
	quote = 0;
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '"'))
			quote = *str;
		else if (quote && *str == quote && (!str[1] || str[1] == sep))
		{
			count++;
			quote = 0;
		}
		else if (!quote && *str != sep && (!str[1] || str[1] == sep))
			count++;
		str++;
	}
	return (count);
}

int	strlen_till_sep(char *str, char sep)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (*str)
	{
		if (!quote && (*str == '"' || *str == '\''))
			quote = *str;
		else if (quote && *str == quote)
			quote = 0;
		else if (!quote && *str == sep)
			break ;
		else
			i++;
		str++;
	}
	return (i);
}

char	*allocate_word(char **str, int size)
{
	char	*word;
	char	quote;
	int		i;

	word = (char *)malloc(sizeof(char) * (size + 1));
	quote = 0;
	i = 0;
	if (!word)
		return (NULL);
	word[size] = '\0';
	while (i < size)
	{
		if (!quote && (**str == '\'' || **str == '"'))
			quote = *(*str)++;
		else if (quote && **str == quote)
		{
			quote = 0;
			(*str)++;
		}
		else
			word[i++] = *(*str)++;
	}
	if (**str)
		(*str)++;
	return (word);
}

char	**shell_split(char *str, char sep)
{
	int		split_count;
	char	**result;
	int		word_i;
	int		word_len;

	split_count = get_split_count(str, sep);
	result = malloc(sizeof(char *) * (split_count + 1));
	if (!result)
		return (NULL);
	word_i = 0;
	while (*str)
	{
		if (*str == sep)
			str++;
		else
		{
			word_len = strlen_till_sep(str, sep);
			result[word_i] = allocate_word(&str, word_len);
			word_i++;
		}
	}
	result[word_i] = NULL;
	return (result);
}
