/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ss_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:19:12 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/20 15:14:28 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	duplicate_fd(int fd, int dest)
{
	int	backup_fd;

	backup_fd = dup(dest);
	dup2(fd, dest);
	close(fd);
	return (backup_fd);
}


int	ss_redirect(t_command *cmd_list, t_shell *shell)
{
	t_command	*cmd;

	cmd = get_ss_cmd(cmd_list, shell, 1);
	if (cmd->delimiters[0])
	{
		shell->mfd.hd_fd = cmd->heredoc_fd;
		if (shell->mfd.hd_fd == -1)
			return (FAILURE);
		shell->mfd.in_fd = duplicate_fd(shell->mfd.hd_fd, STDIN_FILENO);
	}	
	else if (cmd->in_file_count != 0)
	{
		shell->mfd.s_in_fd = redirect_from_file(cmd, shell->depth);
		if (shell->mfd.s_in_fd == -1)
			return (FAILURE);
	}
	if (cmd->out_file_count != 0)
	{
		shell->mfd.s_out_fd = redirect_to_file(cmd, shell->depth);
		if (shell->mfd.s_out_fd == -1)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	get_ss_next_operator(t_command *cmd, t_shell *shell, int change)
{
	int	op;

	while (cmd && cmd->op.depth != shell->depth)
		cmd = cmd->next;
	if (!cmd)
		return (0);
	op = cmd->op.type;
	if (change)
		cmd->op.type = 0;
	return (op);
}

t_command	*get_ss_cmd(t_command *cmd, t_shell *shell, int change)
{
	t_command	*tmp;

	tmp = cmd;
	while (cmd && cmd->op.depth != shell->depth)
		cmd = cmd->next;
	if (!cmd)
	{
		while (tmp && tmp->depth - 1 != shell->depth)
			tmp = tmp->next;
		cmd = tmp;
	}
	if (change)
		cmd->op.type = 0;
	return (cmd);
}
