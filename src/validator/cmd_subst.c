/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_subst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:14:37 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/23 16:48:49 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ns_validate_cmd_subst(char *input)
{
	char	quote;

	quote = 0;
	while (*input)
	{
		if (!quote && *input == '\'')
			quote = *input;
		else if (quote && *input == quote)
			quote = 0;
		else if (!quote && *input == '$' && *(input + 1) == '(')
			return (false);
		input++;
	}
	return (true);
}
