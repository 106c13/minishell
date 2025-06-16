/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:02:03 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/16 17:02:08 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate(char *input)
{
	int		op_type;
	char	quote;

	op_type = 0;
	quote = 0;
	if (get_operator_type(input) != 0)
		return (printerr_one("Invalid input"), 1);
	while (*input)
	{
		if (!quote)
		{
			if (is_quote(*input))
				quote = *input;
			if (!op_type && get_operator_type(input) != 0)
				op_type = get_operator_type(input);
			else if (op_type != 0 && get_operator_type(input) == 0)
				op_type = 0;
		}
		else if (quote == *input)
			quote = 0;
		input++;
	}
	if (quote || op_type)
		return (printerr_one("Invalid input"), 1);
	return (0);
}
