/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:49 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/23 18:20:04 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_spaces(char *str);

bool	ns_validate_op(char *input);

bool	is_valid_two_char_op(char *p, char *start)
{
	if (p - 1 < start)
		return (false);
	if ((p[0] == '&' && p[-1] == '&') || (p[0] == '|' && p[-1] == '|')
		|| (p[0] == '>' && p[-1] == '>') || (p[0] == '<' && p[-1] == '<'))
		return (true);
	return (false);
}

bool	is_valid_op_before_paren(char *pos, char *start)
{
	char	*p;

	p = pos - 1;
	while (p >= start && (*p == ' ' || *p == '\t'))
		p--;
	if (p < start)
		return (true);
	if (*p == '(')
		return (false);
	if (is_valid_two_char_op(p, start))
		return (true);
	if (*p == '|' || *p == '<' || *p == '>')
		return (true);
	return (false);
}

bool	is_operator_char(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '>' || c == '<');
}

char	*find_closing_paren(char *input)
{
	char	quote;
	int		paren_level;

	paren_level = 1;
	quote = 0;
	input++;
	while (*input && paren_level > 0)
	{
		if (!quote && (*input == '\'' || *input == '"'))
			quote = *input;
		else if (quote && *input == quote)
			quote = 0;
		else if (!quote)
		{
			if (*input == '(')
				paren_level++;
			else if (*input == ')')
				paren_level--;
		}
		input++;
	}
	if (paren_level != 0)
		return (NULL);
	return (input);
}
