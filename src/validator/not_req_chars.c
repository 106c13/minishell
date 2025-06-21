/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_req_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:29:12 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/21 20:51:27 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

static bool	is_forbidden(char c)
{
	return (c == ';' || c == '#' || c == '\\' || c == '&'
		|| c == '[' || c == ']' || c == '{' || c == '}');
}

bool	ns_validate_not_required_chars(char *input)
{
	char	quote;

	quote = 0;
	while (*input)
	{
		if (!quote && (*input == '\'' || *input == '"'))
			quote = *input;
		else if (quote && *input == quote)
			quote = 0;
		else if (!quote)
		{
			if (*input == '&' && *(input + 1) == '&')
			{
				input += 2;
				continue ;
			}
			if (is_forbidden(*input))
				return (false);
		}
		input++;
	}
	return (quote == 0);
}
