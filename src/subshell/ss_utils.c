/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ss_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:19:12 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/18 17:43:05 by haaghaja         ###   ########.fr       */
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


int	ss_redirect(t_shell *shell)
{
	if (shell->mfd.pipefd[0] != -1)
		shell->mfd.in_fd = duplicate_fd(shell->mfd.pipefd[0], STDIN_FILENO);
	if (shell->mfd.pipefd[1] != -1)
		shell->mfd.out_fd = duplicate_fd(shell->mfd.pipefd[1], STDOUT_FILENO);
	return (SUCCESS);
}

