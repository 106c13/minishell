/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:34:52 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/20 15:14:53 by haaghaja         ###   ########.fr       */
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

int	run_subshell(t_command **cmd, t_shell *shell)
{
	get_ss_next_operator(*cmd, shell, 1);
	ss_redirect(*cmd, shell);
	//printf("RUNNING %s %s %d\n", (*cmd)->args[0].str, (*cmd)->args[1].str, getpid());
	//printf("$RUNNING %d %d\n", getpid(), shell->mfd.out_fd);
	shell->depth++;
//	printf("REDIRECT %s %d %d\n", (*cmd)->cmd->str, shell->mfd.pipefd[0], shell->mfd.pipefd[1]);
	//printf("SUBSHEll %d [%d %d]\n", getpid(), shell->mfd.s_in_fd, shell->mfd.s_out_fd);
	start_exec(*cmd, shell);
	shell->mfd.is_redirected = 1;
	ss_restore_fd(&shell->mfd);
	restore_fd(&shell->mfd);
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
		//close(0);
		//close(1);
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
	//	printf("IN FORK %d\n", getpid());
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
