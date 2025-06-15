/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:22:44 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/15 16:40:05 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	duplicate_fd(int fd, int dest)
{
	int	backup_fd;

	backup_fd = dup(dest);
	dup2(fd, dest);
	close(fd);
	return (backup_fd);
}

int	redirect_from_file(t_command *cmd)
{
	int		i;
	int		fd;
	t_arg	file;

	i = 0;
	fd = -1;
	while (i < cmd->args_count)
	{
		file = cmd->args[i++];
		if (file.file != 1)
			continue ;
		if (fd != -1)
			close(fd);
		fd = open(file.str, O_RDONLY);
		if (fd == -1)
		{
			printf("minishell: %s: No such file or directory\n", file.str);
			return (-1);
		}
	}
	return (duplicate_fd(fd, STDIN_FILENO));
}

int	redirect_to_file(t_command *cmd)
{
	int		i;
	int		fd;
	t_arg	file;

	i = 0;
	fd = -1;
	while (i < cmd->args_count)
	{
		file = cmd->args[i++];
		if (file.file != 2)
			continue ;
		if (fd != -1)
			close(fd);
		if (file.append)
			fd = open(file.str, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(file.str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return (-1);
	}
	return (duplicate_fd(fd, STDOUT_FILENO));
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
