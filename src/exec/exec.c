/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:18:17 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/13 18:39:33 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void collect_finished_jobs(t_shell *shell)
{
	t_job *curr = shell->job_list;
	t_job *prev = NULL;
	int status;
	pid_t result;

	while (curr)
	{
		result = waitpid(curr->pid, &status, 0);
		//printf("PID: %d STATUS: %d\n", curr->pid, status);
		if (result > 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->job_list = curr->next;
			//free(curr->cmd_str);
			t_job *to_free = curr;
			free(to_free);
		}
		else
			prev = curr;
		curr = curr->next;
	}
}

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





int	setup_redirection(t_command *cmd)
{
		int	i;
		int	fd;
		int	bfd;

		i = 0;
		bfd = dup(STDOUT_FILENO);
		while (i < cmd->out_file_count)
		{
			fd = open(cmd->output_files[i].arg, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
				return (-1);
			i++;
			if (i == cmd->out_file_count)
				dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		return (bfd);
}

void	restore_fd(int	fd)
{
		if (fd < 0)
			return ;
		dup2(fd, STDOUT_FILENO);
		close(fd);
}

void exec_in_pipe(t_command *cmd, t_shell *shell, int *pipefd, int in_fd)
{
	pid_t	pid;
	int		bfd;

	bfd = -1;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		set_default_signals();
		if (cmd->out_file_count != 0)
			bfd = setup_redirection(cmd);
		else
		{ 
				if (in_fd != -1)
				{
					dup2(in_fd, STDIN_FILENO);
					close(in_fd);
				}
				if (pipefd[1] != -1)
				{
					dup2(pipefd[1], STDOUT_FILENO);
					close(pipefd[1]);
					close(pipefd[0]);
				}
		}
		expand_cmd_args(cmd, shell);
		if (is_builtin(cmd))
			shell->exec_result = exec_builtin(cmd, shell);
		else
			shell->exec_result = exec_bin(cmd, shell);
		restore_fd(bfd);
		close(bfd);
		exit(shell->exec_result);
	}
	else if (pid > 0)
	{
		add_job(shell, pid);
		//waitpid(pid, NULL, 0);
	}
	else
	{
		// handle this
	}
}

int	exec_ordinary(t_command *cmd, t_shell *shell, int in_fd)
{
	pid_t pid;
	int bfd = -1;

	expand_cmd_args(cmd, shell);
	if (is_builtin(cmd))
	{
		if (cmd->out_file_count != 0)
			bfd = setup_redirection(cmd);
		if (in_fd != -1)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		shell->exec_result = exec_builtin(cmd, shell);
		restore_fd(in_fd);
		restore_fd(bfd);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			set_default_signals();
			if (cmd->out_file_count != 0)
				bfd = setup_redirection(cmd);
			if (in_fd != -1)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			shell->exec_result = exec_bin(cmd, shell);
			restore_fd(in_fd);
			restore_fd(bfd);
			exit(shell->exec_result);
		}
		else if (pid > 0)
		{
			if (in_fd != -1)
				close(in_fd);
			waitpid(pid, &shell->exec_result, 0);
		}
	}
	return 0;
}

int exec_cmd(t_command *cmd, t_shell *shell)
{
	int pipefd[2] = {-1, -1};
	int prev_fd = -1;

	while (cmd)
	{
		if (cmd->operator_type == PIPE)
		{
			pipe(pipefd);
			exec_in_pipe(cmd, shell, pipefd, prev_fd);
			if (prev_fd != -1)
				close(prev_fd);
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		else
		{
			exec_ordinary(cmd, shell, prev_fd);
			if (prev_fd != -1)
				close(prev_fd);
			prev_fd = -1;
		}

		if (cmd->operator_type == AND && shell->exec_result != 0)
			cmd = cmd->next;
		else if (cmd->operator_type == OR && shell->exec_result == 0)
			cmd = cmd->next;
		if (cmd)
			cmd = cmd->next;
	}
	collect_finished_jobs(shell);
	return shell->exec_result;
}
