/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:51:26 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/31 16:58:10 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_split_count(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
		{
			str++;
			continue ;
		}
		count++;
		while (*str && *str != c)
		{
			str++;
		}
	}
	return (count);
}

static int	strlen_till_sep(const char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
	{
		len++;
	}
	return (len);
}

static char	*allocate_word(const char *str, int len)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split(const char *str, char c)
{
	int		split_count;
	char	**result;
	int		word_i;
	int		word_len;

	split_count = get_split_count(str, c);
	result = malloc(sizeof(char *) * (split_count + 1));
	if (!result)
		return (NULL);
	word_i = 0;
	while (*str)
	{
		if (*str == c)
		{
			str++;
			continue ;
		}
		word_len = strlen_till_sep(str, c);
		result[word_i] = allocate_word(str, word_len);
		str += word_len;
		word_i++;
	}
	result[word_i] = NULL;
	return (result);
}
