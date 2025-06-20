/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:36:28 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/20 17:45:55 by haaghaja         ###   ########.fr       */
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

int	check_heredoc(t_command *cmd, t_shell *shell)
{
	if (shell->mfd.hd_fd == -1)
		shell->mfd.hd_fd = cmd->heredoc_fd;
	if (shell->mfd.hd_fd == -1)
		return (FAILURE);
	shell->mfd.in_fd = duplicate_fd(shell->mfd.hd_fd, STDIN_FILENO);
	shell->mfd.is_redirected = 1;
	return (SUCCESS);
}

int	check_in(t_command *cmd, t_shell *shell)
{
	shell->mfd.in_fd = redirect_from_file(cmd, cmd->depth);
	if (shell->mfd.in_fd == -1)
		return (FAILURE);
	shell->mfd.is_redirected = 1;
	return (SUCCESS);
}

int	check_out(t_command *cmd, t_shell *shell)
{
	int	tmp;

	tmp = redirect_to_file(cmd, cmd->depth);
	if (tmp == -1)
		return (FAILURE);
	if (tmp != -2)
	{
		shell->mfd.out_fd = tmp;
		shell->mfd.is_redirected = 1;
	}
	return (SUCCESS);
}
