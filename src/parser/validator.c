/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:23:38 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 18:04:55 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <ctype.h>

int	is_empty(char *str);

static int	check_quotes(const char *str)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			if (!quote)
				quote = *str;
			else if (quote == *str)
				quote = 0;
		}
		str++;
	}
	return (quote == 0);
}

int	has_content_inside(char *str, int start);

int	skip_quote(char *str, int i);

static int	check_brackets(char *str)
{
	int	i;
	int	depth;

	i = -1;
	depth = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i = skip_quote(str, i);
		else if (str[i] == '(')
		{
			if (!has_content_inside(str, i))
				return (0);
			depth++;
		}
		else if (str[i] == ')')
		{
			if (depth == 0)
				return (0);
			depth--;
		}
		if (i == -1)
			return (0);
	}
	return (depth == 0);
}

int	skip_quote(char *str, int i);

int	check_double_op(char *str, int *i);

int	check_single_pipe(char *str, int i);

static int	check_syntax(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i = skip_quote(str, i);
			if (i == -1)
				return (0);
		}
		else if ((str[i] == '&' && str[i + 1] == '&')
			|| (str[i] == '|' && str[i + 1] == '|'))
		{
			if (!check_double_op(str, &i))
				return (0);
			continue ;
		}
		else if (str[i] == '|')
		{
			if (!check_single_pipe(str, i))
				return (0);
		}
	}
	return (1);
}

int	check_invalid_chars(char *str)
{
	int		i;
	char	quote;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (!str[i])
				return (0);
		}
		else if (str[i] == ';')
			return (0);
		else if (str[i] == '&')
		{
			if (str[i + 1] != '&')
				return (0);
			i++;
		}
	}
	return (1);
}

int	validate(char *input)
{
	if (is_empty(input))
		return (printerr_one("syntax error: empty input"), 1);
	if (!check_invalid_chars(input))
		return (printerr_one("syntax error: invalid character ';' or '&'"), 1);
	if (!check_quotes(input))
		return (printerr_one("syntax error: unclosed quote"), 1);
	if (!check_brackets(input))
		return (printerr_one("syntax error: invalid_brackets"), 1);
	if (!check_syntax(input))
		return (printerr_one("syntax error: near unexpected token"), 1);
	return (0);
}
