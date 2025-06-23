/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:42:49 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/23 17:48:26 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_spaces(char *str);

bool	ns_validate_empty_parens(char *input)
{
	char	quote;
	char	*p;

	while (*input)
	{
		if (!quote && (*input == '\'' || *input == '"'))
			quote = *input;
		else if (quote && *input == quote)
			quote = 0;
		else if (!quote && *input == '(')
		{
			p = input + 1;
			while (*p && ft_isspace(*p))
				p++;
			if (*p == ')')
				return (false);
		}
		input++;
	}
	return (true);
}

bool	ns_validate_brackets(char *input)
{
	int		count;
	char	quote;

	count = 0;
	quote = 0;
	while (*input)
	{
		if (!quote && (*input == '\'' || *input == '"'))
			quote = *input;
		else if (quote && *input == quote)
			quote = 0;
		else if (!quote)
		{
			if (*input == '(')
				count++;
			else if (*input == ')')
			{
				count--;
				if (count < 0)
					return (false);
			}
		}
		input++;
	}
	return (count == 0);
}
