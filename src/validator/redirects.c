/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:29:12 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/24 15:59:52 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

char	*skip_spaces(char *str);

static char	*manage_quotes(char *input)
{
	char	quote;

	quote = *input++;
	while (*input && *input != quote)
		input++;
	if (*input == quote)
		input++;
	return (input);
}

bool	ns_validate_redirects(char *input)
{
	char	op;

	while (*input)
	{
		if (*input == '\'' || *input == '"')
			input = manage_quotes(input);
		else if (*input == '<' || *input == '>')
		{
			op = *input;
			if (*(input + 1) && *(input + 1) == op)
				input += 2;
			else
				input += 1;
			input = skip_spaces(input);
			if (!*input || *input == '<' || *input == '>' || is_eow(*input))
				return (false);
		}
		else
			input++;
	}
	return (true);
}
