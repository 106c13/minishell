/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:34:52 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/25 21:39:36 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	setup_pipe_fds(t_shell *shell, int *prev_read_fd)
{
	*prev_read_fd = -1;
	if (shell->mfd.pipefd[0] != -1)
		*prev_read_fd = shell->mfd.pipefd[0];
	if (pipe(shell->mfd.pipefd) == -1)
		return (-1);
	return (0);
}

static int	exec_pipe(t_command **cmd, t_shell *shell, int prev_read_fd)
{
	if (prev_read_fd != -1)
	{
		dup2(prev_read_fd, STDIN_FILENO);
		close(prev_read_fd);
	}
	else
	{
		dup2(shell->mfd.pipefd[1], STDOUT_FILENO);
		close(shell->mfd.pipefd[1]);
		shell->mfd.pipefd[1] = -1;
	}
	return (run_subshell(cmd, shell));
}

int	run_ss_in_pipe(t_command **cmd, t_shell *shell)
{
	pid_t	pid;
	int		prev_read_fd;

	if (setup_pipe_fds(shell, &prev_read_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		close(shell->mfd.pipefd[0]);
		shell->mfd.pipefd[0] = -1;
		exec_pipe(cmd, shell, prev_read_fd);
		cleanup(shell);
		exit(shell->exec_result);
	}
	else if (pid > 0)
	{
		close(shell->mfd.pipefd[1]);
		shell->mfd.pipefd[1] = -1;
		if (prev_read_fd != -1)
			close(prev_read_fd);
		add_job(shell, pid);
	}
	return (0);
}

int	run_ss_ordinary(t_command **cmd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		run_subshell(cmd, shell);
		cleanup(shell);
		exit(shell->exec_result);
	}
	else if (pid > 0)
	{
		waitpid(pid, &shell->exec_result, 0);
		close_pipes(&shell->mfd);
		if (shell->exec_result > 256)
			shell->exec_result /= 256;
	}
	return (0);
}
