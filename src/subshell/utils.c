/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:15:03 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/20 17:10:09 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*skip_command(t_command *cmd, int depth)
{
	while (cmd)
	{
		if (cmd->depth == depth && cmd->last_in_group)
			break ;
		if (cmd->next && cmd->next->depth == depth - 1)
			break ;
		cmd = cmd->next;
	}
	if (cmd)
		cmd->last_in_group = 0;
	return (cmd);
}

void	ss_restore_fd(t_mfd *mfd)
{
	if (mfd->s_in_fd >= 0)
	{
		dup2(mfd->s_in_fd, STDIN_FILENO);
		close(mfd->s_in_fd);
		mfd->s_in_fd = -1;
	}
	if (mfd->s_out_fd >= 0)
	{
		dup2(mfd->s_out_fd, STDOUT_FILENO);
		close(mfd->s_out_fd);
		mfd->s_out_fd = -1;
	}
}
