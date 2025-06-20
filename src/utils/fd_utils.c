/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:22:44 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/20 18:01:45 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	duplicate_fd(int fd, int dest)
{
	int	backup_fd;

	if (fd == -2)
		return (-2);
	backup_fd = dup(dest);
	dup2(fd, dest);
	close(fd);
	return (backup_fd);
}

int	redirect_from_file(t_command *cmd, int depth)
{
	int		i;
	int		fd;
	int		reded;
	t_arg	file;

	i = 0;
	fd = -2;
	reded = 0;
	while (i < cmd->args_count)
	{
		file = cmd->args[i++];
		if (file.file != 1)
			continue ;
		if (depth == file.depth)
			reded = 1;
		if (depth != file.depth && reded)
			continue ;
		if (fd != -2)
			close(fd);		
		fd = open(file.str, O_RDONLY);
		if (fd == -1)
		{
			printerr_two(file.str, "No such file or directory");
			return (-1);
		}
	}
	return (duplicate_fd(fd, STDIN_FILENO));
}

int	redirect_to_file(t_command *cmd, int depth)
{
	int		i;
	int		fd;
	t_arg	file;

	i = 0;
	fd = -2;
	while (i < cmd->args_count)
	{
		file = cmd->args[i++];
		if (file.file != 2 || file.depth != depth)
			continue ;
		if (fd != -2)
			close(fd);
		if (file.append)
			fd = open(file.str, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(file.str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			printf("minishell: %s: Permission denied or file error\n", file.str);
			return (-1);
		}
	}
	return (duplicate_fd(fd, STDOUT_FILENO));
}

int	setup_redirection(t_command *cmd, t_shell *shell)
{
	if (cmd->delimiters[0] && check_heredoc(cmd, shell) != SUCCESS)
		return (FAILURE);
	else if (cmd->in_file_count != 0)
	{
		if (check_in(cmd, shell) != SUCCESS)
			return (FAILURE);
	}
	else if (shell->mfd.pipefd[0] != -1)
	{
		shell->mfd.in_fd = duplicate_fd(shell->mfd.pipefd[0], STDIN_FILENO);
		shell->mfd.is_redirected = 1;
	}
	if (cmd->out_file_count != 0)
	{
		if (check_out(cmd, shell) != SUCCESS)
			return (FAILURE);
	}
	else if (shell->mfd.pipefd[1] != -1)
	{
		shell->mfd.out_fd = duplicate_fd(shell->mfd.pipefd[1], STDOUT_FILENO);
		shell->mfd.is_redirected = 1;
	}
	return (SUCCESS);
}

void	restore_fd(t_mfd *mfd)
{
	if (mfd->is_redirected == -1)
		return ;
	if (mfd->in_fd >= 0)
	{
		dup2(mfd->in_fd, STDIN_FILENO);
		close(mfd->in_fd);
		mfd->in_fd = -1;
	}
	if (mfd->out_fd >= 0)
	{
		dup2(mfd->out_fd, STDOUT_FILENO);
		close(mfd->out_fd);
		mfd->out_fd = -1;
	}
}
