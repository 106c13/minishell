/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pairs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:29:12 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/21 19:51:56 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

bool	ns_validate_quotes(char *input)
{
	char	quote;

	while (*input)
	{
		if (*input == '\'' || *input == '"')
		{
			quote = *input++;
			while (*input && *input != quote)
				input++;
			if (!*input)
				return (false);
		}
		if (*input)
			input++;
	}
	return (true);
}

bool	ns_validate_brackets(char *input)
{
	int	count;

	count = 0;
	while (*input)
	{
		if (*input == '(')
			count++;
		else if (*input == ')')
		{
			count--;
			if (count < 0)
				return (false);
		}
		input++;
	}
	return (count == 0);
}
