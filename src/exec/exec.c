/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:01:39 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/18 17:57:32 by azolotar         ###   ########.fr       */
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

//===================================================================

int	exec_cmd(t_command *cmd, t_shell *shell)
{
	if (setup_redirection(cmd, shell) == FAILURE)
		return (FAILURE);
	if (!cmd->cmd)
		return (0);
	if (is_builtin(cmd))
		shell->exec_result = exec_builtin(cmd, shell);
	else
	{
		set_default_signals();
		shell->exec_result = exec_bin(cmd, shell);
	}
	restore_fd(&shell->mfd);
	return (0);
}

int	setup_pipe_fds(t_shell *shell, int *prev_read_fd)
{
	*prev_read_fd = -1;
	if (shell->mfd.pipefd[0] != -1)
		*prev_read_fd = shell->mfd.pipefd[0];
	if (pipe(shell->mfd.pipefd) == -1)
		return (-1);
	return (0);
}

int	exec_pipe(t_command *cmd, t_shell *shell, int prev_read_fd)
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
	pid_t pid;

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
	return 0;
}


t_command	*skip_command(t_command *cmd, int depth)
{
	while (cmd)
	{
		//printf("Checking %s %d %d\n", cmd->cmd->str, cmd->depth, depth);
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
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		shell->depth++;
		start_exec(*cmd, shell);
		cleanup(shell);
		exit(shell->exec_result);
	}
	else if (pid > 0)
	{
		//printf("STARTED PID %d\n", pid);
		waitpid(pid, &shell->exec_result, 0);
		*cmd = skip_command(*cmd, shell->depth + 1);
		//if (*cmd)
		//	printf("%d STOPPED ON %s %s\n", pid, (*cmd)->cmd->str, (*cmd)->args[1].str);
		set_exec_result(shell, shell->exec_result);
	}
	return (0);
}

int start_exec(t_command *cmd, t_shell *shell)
{
	while (cmd)
	{
		expand_args(cmd, shell);
//		print_cmd(cmd);
		if (cmd->depth > shell->depth)
			run_subshell(&cmd, shell);
		else if (cmd->depth == shell->depth)
		{
			if (cmd->operator_type == PIPE)
				start_pipe(cmd, shell);
			else
				exec_ordinary(cmd, shell);
		}
		else
			break ;
		if (!cmd || cmd->last_in_group || shell->exec_result == 130)
			break ;
		if (cmd->operator_type == AND && shell->exec_result != 0)
			cmd = cmd->next;
		else if (cmd->operator_type == OR && shell->exec_result == 0)
			cmd = cmd->next;
		if (cmd)
			cmd = cmd->next;
	}
	collect_finished_jobs(shell);
	close_pipes(&shell->mfd);
	return (shell->exec_result);
}
