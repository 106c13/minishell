/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:24:36 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/15 18:07:10 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_whitespace(char c)
{
	return (!c || c == ' ' || c == '\t');
}

void	set_operator(char **str, t_command *cmd)
{
	cmd->operator_type = get_operator_type(*str);
	if (cmd->operator_type == OR || cmd->operator_type == AND)
		*str += 2;
	else
		(*str)++;
}

int	is_eow(char c)
{
	if (is_whitespace(c))
		return (1);
	if (c == '>' || c == '<'
		|| c == '&' || c == '|'
		|| c == '(' || c == ')')
		return (1);
	return (0);
}
