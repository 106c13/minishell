/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:18:17 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/07 17:16:57 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



t_job	*create_job(pid_t pid, int id)
{
	t_job	*job;

	job = malloc(sizeof(t_job));
	if (!job)
		return NULL;
	job->id = id + 1;
	job->pid = pid;
	job->command = NULL;
	job->next = NULL;
	return (job);
}

void	add_job(t_shell *shell, pid_t pid)
{
	t_job *job;

	job = shell->job_list;
	if (!job)
	{
		shell->job_list = create_job(pid, 0);
		return ;
	}
	while (job->next)
		job = job->next;
	job->next = create_job(pid, job->id);
}

int	get_job_id(t_job *job, pid_t pid)
{
	while (job)
	{
		if (job->pid == pid)
			return (job->id);
		job = job->next;
	}
	return (-1);
}

// =================================================







int	exec_in_bg(t_command *cmd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
	{
		add_job(shell, pid);
		printf("[%d] %d\n", get_job_id(shell->job_list, pid), pid);
	}
	if (pid == 0) // CHILD
	{
		interpret_cmd_args(cmd, shell);
		if (is_builtin(cmd))
		{
			shell->exec_result = exec_builtin(cmd, shell);
		}
		else
		{
			shell->exec_result = exec_bin(cmd, shell);
		}
		exit(shell->exec_result);
	}
	return (0); //Change in the future
}

void exec_in_pipe(t_command *cmd, t_shell *shell, int in_fd, int out_fd)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		if (in_fd != -1)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != -1)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		interpret_cmd_args(cmd, shell);
		if (is_builtin(cmd))
			exit(exec_builtin(cmd, shell));
		else
			exit(exec_bin(cmd, shell));
	}
	else
	{
		if (in_fd != -1)
			close(in_fd);
		if (out_fd != -1)
			close(out_fd);
		waitpid(pid, NULL, 0);
	}
}


int	exec_cmd(t_command *cmd, t_shell *shell)
{
	int	pipefd[2];
	int	prev_fd = -1;

	while (cmd)
	{
		if (cmd->oper == PIPE)
		{
			pipe(pipefd);
			exec_in_pipe(cmd, shell, prev_fd, pipefd[1]);
			if (prev_fd != -1)
				close(prev_fd);
			close(pipefd[1]);
			prev_fd = pipefd[0];
			cmd = cmd->next;
			continue ;
		}
		if (prev_fd != -1)
		{
			exec_in_pipe(cmd, shell, prev_fd, -1);
			close(prev_fd);
			prev_fd = -1;
			cmd = cmd->next;
			continue ;
		}
		if (cmd->oper == BG)
		{
			exec_in_bg(cmd, shell);
			cmd = cmd->next;
			continue;
		}
		interpret_cmd_args(cmd, shell);
//		replace_wildcards(cmd);
		if (is_builtin(cmd))
		{
			shell->exec_result = exec_builtin(cmd, shell);
		}
		else
		{
			shell->exec_result = exec_bin(cmd, shell);
		}
		//printf("EXEC STATUS: %d\n", shell->exec_result);
		if (cmd->oper == AND && shell->exec_result != 0)
			break ;
		if (cmd->oper == OR && shell->exec_result == 0)
			break ;
		cmd = cmd->next;
	}
	return (shell->exec_result);
}
