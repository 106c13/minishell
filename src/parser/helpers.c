/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:24:36 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/12 13:26:01 by haaghaja         ###   ########.fr       */
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
	cmd->oper = get_operator_type(*str);
	if (cmd->oper == OR || cmd->oper == AND)
		*str += 2;
	else
		(*str)++;
}
