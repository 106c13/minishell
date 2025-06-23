/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:01:39 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/23 18:55:18 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	close_pipes(t_mfd *mfd)
{
	if (mfd->pipefd[0] != -1)
		close(mfd->pipefd[0]);
	if (mfd->pipefd[1] != -1)
		close(mfd->pipefd[1]);
	mfd->pipefd[0] = -1;
	mfd->pipefd[1] = -1;
}

static int	setup_pipe_fds(t_shell *shell, int *prev_read_fd)
{
	*prev_read_fd = -1;
	if (shell->mfd.pipefd[0] != -1)
		*prev_read_fd = shell->mfd.pipefd[0];
	if (pipe(shell->mfd.pipefd) == -1)
		return (-1);
	return (0);
}

static int	exec_pipe(t_command *cmd, t_shell *shell, int prev_read_fd)
{
	close(shell->mfd.pipefd[0]);
	if (prev_read_fd != -1)
		shell->mfd.pipefd[0] = prev_read_fd;
	else
		shell->mfd.pipefd[0] = -1;
	exec_cmd(cmd, shell);
	cleanup(shell);
	exit(shell->exec_result);
}

int	start_pipe(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	int		prev_read_fd;

	if (setup_pipe_fds(shell, &prev_read_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		exec_pipe(cmd, shell, prev_read_fd);
	else if (pid > 0)
	{
		close(shell->mfd.pipefd[1]);
		if (prev_read_fd != -1)
			close(prev_read_fd);
		shell->mfd.pipefd[1] = -1;
		add_job(shell, pid);
	}
	else
	{
		close_pipes(&shell->mfd);
		if (prev_read_fd != -1)
			close(prev_read_fd);
		return (-1);
	}
	return (0);
}

int	exec_ordinary(t_command *cmd, t_shell *shell)
{
	pid_t	pid;

	if (is_builtin(cmd))
		exec_cmd(cmd, shell);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			exec_cmd(cmd, shell);
			cleanup(shell);
			exit(shell->exec_result);
		}
		else if (pid > 0)
		{
			close_pipes(&shell->mfd);
			waitpid(pid, &shell->exec_result, 0);
			set_exec_result(shell, shell->exec_result);
		}
	}
	return (0);
}
