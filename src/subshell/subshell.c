/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:34:52 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/19 23:25:21 by haaghaja         ###   ########.fr       */
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



int	run_subshell(t_command **cmd, t_shell *shell)
{
	get_ss_next_operator(*cmd, shell, 1);
	ss_redirect(*cmd, shell);
	shell->depth++;
	//printf("REDIRECT %s %d %d\n", (*cmd)->cmd->str, shell->mfd.pipefd[0], shell->mfd.pipefd[1]);
	start_exec(*cmd, shell);
	restore_fd(&shell->mfd);
	return (0);
}


static int	exec_pipe(t_command **cmd, t_shell *shell, int prev_read_fd)
{
	if (prev_read_fd != -1)
		shell->mfd.pipefd[0] = prev_read_fd;
	else
		shell->mfd.pipefd[0] = -1;
	return (run_subshell(cmd, shell));
}


int	run_ss_in_pipe(t_command **cmd, t_shell *shell)
{
	pid_t	pid;
	int		prev_read_fd;

	//printf("PIPE!!!!%s [%d] %d %d\n", (*cmd)->cmd->str, shell->depth, shell->mfd.pipefd[0], shell->mfd.pipefd[1]);
	if (setup_pipe_fds(shell, &prev_read_fd) == -1)
		return (-1);
	//printf("PIPE!!!! AFTER %s [%d] %d %d\n", (*cmd)->cmd->str, shell->depth, shell->mfd.pipefd[0], shell->mfd.pipefd[1]);
	//printf("PREVPIPE: %s %d\n", (*cmd)->cmd->str, prev_read_fd);
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
		//printf("CHILD PID: %d\n", pid);
		close(shell->mfd.pipefd[1]);
		shell->mfd.pipefd[1] = -1;
		if (prev_read_fd != -1)
			close(prev_read_fd);
		//printf("PIPE!!!! MAIN%s [%d] %d %d\n", (*cmd)->cmd->str, shell->depth, shell->mfd.pipefd[0], shell->mfd.pipefd[1]);
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
		//printf("REACHED SUBSHELL CLEANUP %d\n", getpid());
		cleanup(shell);
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
