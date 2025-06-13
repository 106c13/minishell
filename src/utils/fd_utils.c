/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:22:44 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/13 18:58:48 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_from_file(t_command *cmd)
{
	int	fd;
	int	backup_fd;
	int	i;

	i = 0;
	backup_fd = dup(STDIN_FILENO);
	while (i < cmd->in_file_count)
	{
			fd = open(cmd->input_files[i].name, O_RDONLY);
			if (fd == -1)
			{
				printf("minishell: %s: No such file or directory\n", cmd->input_files[i].name);
				return (-1);
			}
			i++;
			if (i == cmd->in_file_count)
				dup2(fd, STDIN_FILENO);
			close(fd);
	}
	return (backup_fd);
}

int	redirect_to_file(t_command *cmd)
{
	int	i;
	int	fd;
	int	backup_fd;

	i = 0;
	backup_fd = dup(STDOUT_FILENO);
	while (i < cmd->out_file_count)
	{
		fd = open(cmd->output_files[i].name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return (-1);
		i++;
		if (i == cmd->out_file_count)
			dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (backup_fd);
}

int	setup_redirection(t_command *cmd, int *in_fd, int *out_fd)
{
	if (cmd->in_file_count != 0)
	{
		*in_fd = redirect_from_file(cmd);
		if (*in_fd == -1)
			return (1);
	}
	if (cmd->out_file_count != 0)
	{
		*out_fd = redirect_to_file(cmd);
		if (*out_fd == -1)
			return (1);
	}
	return (0);
}

void	restore_fd(int	*in_fd, int *out_fd)
{
		if (*in_fd >= 0)
		{
			dup2(*in_fd, STDIN_FILENO);
			close(*in_fd);
			*in_fd = -1;
		}
		if (*out_fd >= 0)
		{
			dup2(*out_fd, STDOUT_FILENO);
			close(*out_fd);
			*out_fd = -1;
		}
}

