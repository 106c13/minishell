/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ss_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:19:12 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/19 21:26:10 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	duplicate_fd(int fd, int dest)
{
	int	backup_fd;

	backup_fd = dup(dest);
	dup2(fd, dest);
	//close(fd);
	return (backup_fd);
}


int	ss_redirect(t_command *cmd_list, t_shell *shell)
{
	t_command	*cmd;

	cmd = get_ss_cmd(cmd_list, shell, 1);
	if (cmd->delimiters[0])
	{
		printf("HEREDOC FD: %d\n", shell->mfd.hd_fd);
		shell->mfd.hd_fd = cmd->heredoc_fd;
		if (shell->mfd.hd_fd == -1)
			return (FAILURE);
		shell->mfd.in_fd = duplicate_fd(shell->mfd.hd_fd, STDIN_FILENO);
	}	
	else if (cmd->in_file_count != 0)
	{
		shell->mfd.in_fd = redirect_from_file(cmd, shell->depth);
		if (shell->mfd.in_fd == -1)
			return (FAILURE);
	}
	else if (shell->mfd.pipefd[0] != -1)
		shell->mfd.in_fd = duplicate_fd(shell->mfd.pipefd[0], STDIN_FILENO);
	if (cmd->out_file_count != 0)
	{
		shell->mfd.out_fd = redirect_to_file(cmd, shell->depth);
		if (shell->mfd.out_fd == -1)
			return (FAILURE);
	}
	else if (shell->mfd.pipefd[1] != -1)
		shell->mfd.out_fd = duplicate_fd(shell->mfd.pipefd[1], STDOUT_FILENO);
	return (SUCCESS);
}

int	get_ss_next_operator(t_command *cmd, t_shell *shell, int change)
{
	int	op;

	while (cmd && cmd->op.depth != shell->depth)
	{
		cmd = cmd->next;
	}
	op = cmd->op.type;
	if (change)
		cmd->op.type = 0;
	return (op);
}

t_command	*get_ss_cmd(t_command *cmd, t_shell *shell, int change)
{
	while (cmd && cmd->op.depth != shell->depth)
		cmd = cmd->next;
	if (change)
		cmd->op.type = 0;
	return (cmd);
}
