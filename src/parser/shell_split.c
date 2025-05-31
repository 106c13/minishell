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
	int	count;
	char	quote;

	count = 0;
	quote = 0;
	while (*str)
	{
		if (!quote)
		{
			if (*str == '"' || *str == '\'')
				quote = *str;
			else if (*str != sep && (*(str + 1) == sep || *(str + 1) == '\0'))
				count++;
		}
		else
		{
			if (*str == quote)
			{
				if (*(str + 1) == sep || *(str + 1) == '\0')
					count++;
				quote = 0;
			}
		}	
		str++;
	}
	//printf("SIZE: %d\n", count);
	return (count);
}

static int	strlen_till_sep(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
	{
		len++;
	}
	//printf("STR SIZE: %d\n", len);
	return (len);
}

static char	*allocate_word(char *str, int len)
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

int	strlen_till_quote(char *str, char sep)
{
	int	quote;
	int	size;

	quote = 0;
	size = 0;
	while (*str)
	{
		if (!quote)
		{
			if (*str == sep)
				break ;
			else if (*str == '"' || *str == '\'')
				quote = *str;
			else
				size++;
		}
		else
		{
			if (*str != quote)
				size++;
			else
				quote = 0;
		}
		str++;
	}
	//printf("STR SIZE: %d\n", size);
	return (size);
}

char	*allocate_quote(char **str, int	size)
{
	char	*word;
	char	quote;
	int	i;

	word = (char *)malloc(sizeof(char) + (size + 1));
	if (!word)
		return (NULL);
	word[size] = '\0';
	quote = 0;
	i = 0;
	while (i < size)
	{
		if (!quote)
		{
			if (**str == '"' || **str == '\'')
				quote = **str;
			else
			{
				word[i] = **str;
				i++;
			}
		}
		else
		{
			if (**str != quote)
			{
				word[i] = **str;
				i++;
			}
			else
				quote = 0;
		}
		(*str)++;
	}
	(*str)++;
	//printf("STR: %s\n", *str);
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
		{
			str++;
			continue ;
		}
		if (*str == '"' || *str == '\'')
		{
			word_len = strlen_till_quote(str, sep);
			result[word_i] = allocate_quote(&str, word_len);
			word_i++;
		}
		else
		{
			word_len = strlen_till_sep(str, sep);
			result[word_i] = allocate_word(str, word_len);
			str += word_len;
			word_i++;
		}
	}
	result[word_i] = NULL;
	return (result);
}
