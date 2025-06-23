/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:49 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/23 18:37:31 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_spaces(char *str);

bool	ns_validate_op(char *input);

char	*find_closing_paren(char *input);

bool	is_operator_char(char c);

bool	is_valid_op_before_paren(char *pos, char *start);

bool	is_valid_two_char_op(char *p, char *start);

static bool	ns_validate_paren_content(char *start, char *end)
{
	size_t	len;
	char	*substr;
	bool	res;

	len = end - start;
	substr = malloc(len + 1);
	if (!substr)
		return (false);
	ft_memcpy(substr, start, len);
	substr[len] = '\0';
	res = ns_validate_op(substr);
	free(substr);
	return (res);
}

static bool	validate_inside_parens(char *input, char *close)
{
	char	*inside;

	inside = input + 1;
	while (inside < close - 1 && (*inside == ' ' || *inside == '\t'))
		inside++;
	if (inside == close - 1)
		return (false);
	if (!ns_validate_paren_content(input + 1, close - 1))
		return (false);
	return (true);
}

static bool	validate_after_parens(char *close)
{
	char	*after;

	after = close;
	while (*after == ' ' || *after == '\t')
		after++;
	if (*after && !is_operator_char(*after) && *after != '\0' && *after != '\n')
		return (false);
	return (true);
}

bool	ns_validate_parens_and_context(char *input)
{
	char	*start;
	char	quote;
	char	*close;

	start = input;
	quote = 0;
	input = skip_spaces(input);
	while (*input)
	{
		if (!quote && (*input == '\'' || *input == '"'))
			quote = *input;
		else if (quote && *input == quote)
			quote = 0;
		else if (!quote && *input == '(')
		{
			if (!is_valid_op_before_paren(input, start))
				return (false);
			close = find_closing_paren(input);
			if (!close)
				return (false);
			if (!validate_inside_parens(input, close))
				return (false);
			if (!validate_after_parens(close))
				return (false);
			input = close - 1;
		}
		input++;
	}
	return (true);
}
