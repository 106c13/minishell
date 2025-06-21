/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:24:23 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/21 21:08:23 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

static int	is_op(char *str)
{
	if (!str || !*str)
		return (0);
	if (str[0] == '&' && str[1] && str[1] == '&')
		return (2);
	if (str[0] == '|' && str[1] && str[1] == '|')
		return (2);
	if (str[0] == '|')
		return (1);
	return (0);
}

char	*skip_spaces(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

bool	ns_validate_op(char *input)
{
	bool	has_cmd;
	int		len;

	has_cmd = false;
	while (*input)
	{
		input = skip_spaces(input);
		if (!*input)
			break ;
		len = is_op(input);
		if (len > 0)
		{
			if (!has_cmd)
				return (false);
			input += len;
			input = skip_spaces(input);
			if (!*input || *input == ')' || is_op(input) > 0)
				return (false);
			has_cmd = false;
			continue ;
		}
		has_cmd = !ft_isspace(*input);
		input++;
	}
	return (true);
}
