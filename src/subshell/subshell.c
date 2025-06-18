/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:34:52 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/18 23:23:27 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	close_pipes(t_mfd *mfd)
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

t_command	*skip_command(t_command *cmd, int depth)
{
	while (cmd)
	{
		if (cmd->depth == depth && cmd->last_in_group)
			break ;
		if (cmd->next && cmd->next->depth ==  depth - 1)
			break ;
		cmd = cmd->next;
	}
	if (cmd)
		cmd->last_in_group = 0;
	return (cmd);
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


int	run_subshell(t_command **cmd, t_shell *shell)
{
	get_ss_next_operator(*cmd, shell, 1);
	shell->depth++;
	ss_redirect(shell);
	start_exec(*cmd, shell);
	exit(shell->exec_result);
}


static int	exec_pipe(t_command **cmd, t_shell *shell, int prev_read_fd)
{
	close(shell->mfd.pipefd[0]);
	if (prev_read_fd != -1)
		shell->mfd.pipefd[0] = prev_read_fd;
	else
		shell->mfd.pipefd[0] = -1;
	run_subshell(cmd, shell);
	exit(shell->exec_result);
}


int	run_ss_in_pipe(t_command **cmd, t_shell *shell)
{
	pid_t	pid;
	int		prev_read_fd;

	//printf("PIPE!!!! %d %d\n", shell->mfd.pipefd[0], shell->mfd.pipefd[0]);
	if (setup_pipe_fds(shell, &prev_read_fd) == -1)
		return (-1);
	//printf("PIPE!!!! AFTER %d %d\n", shell->mfd.pipefd[0], shell->mfd.pipefd[1]);
	pid = fork();
	if (pid == 0)
	{
		close(shell->mfd.pipefd[0]);
		exec_pipe(cmd, shell, prev_read_fd);
	}
	else if (pid > 0)
	{
		close(shell->mfd.pipefd[1]);
		if (prev_read_fd != -1)
			close(prev_read_fd);
		shell->mfd.pipefd[1] = -1;
		//printf("PIPE!!!! MAIN AFTER %d %d\n", shell->mfd.pipefd[0], shell->mfd.pipefd[1]);
		add_job(shell, pid);
		*cmd = skip_command(*cmd, shell->depth + 1);
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

int	run_ss_ordinary(t_command **cmd, t_shell *shell)
{
	pid_t pid;

	//printf("ORD!!!! %d %d\n", shell->mfd.pipefd[0], shell->mfd.pipefd[1]);
	pid = fork();
	if (pid == 0)
	{
		run_subshell(cmd, shell);
		exit(shell->exec_result);
	}
	else if (pid > 0)
	{
		waitpid(pid, &shell->exec_result, 0);
		close_pipes(&shell->mfd);	
		*cmd = skip_command(*cmd, shell->depth + 1);
		set_exec_result(shell, shell->exec_result);
	}
	return 0;
}
