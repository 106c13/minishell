/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:36:44 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/25 21:03:03 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_multiple_file(t_arg *args, int n)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < n)
	{
		if (args[i].file != 0 && args[i].wed == 1)
			count++;
		if (count > 1)
			return (1);
		i++;
	}
	return (0);
}

int	is_failed(int status)
{
	if (status == 0 || status == 130 || status == 131)
		return (0);
	return (1);
}

t_command	*skip_norm(t_command *cmd, t_shell *shell, t_oper *op)
{
	while (cmd)
	{
		*op = cmd->op;
		cmd = cmd->next;
		if (cmd && cmd->depth == shell->depth)
			break ;
		if (op->depth == shell->depth)
			break ;
	}
	return (cmd);
}

t_command	*go_to_next_cmd(t_command *cmd, t_shell *shell)
{
	t_oper	op;

	op = cmd->op;
	cmd = cmd->next;
	if (op.depth < shell->depth)
		return (NULL);
	while (cmd && op.depth != shell->depth)
	{
		op = cmd->op;
		cmd = cmd->next;
	}
	while (cmd)
	{
		if ((op.type == AND && shell->exec_result == 0)
			|| (op.type == OR && is_failed(shell->exec_result))
			|| (op.type == PIPE && shell->exec_result == 0))
			return (cmd);
		cmd = skip_norm(cmd, shell, &op);
	}
	return (cmd);
}
