/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:18:17 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/12 14:29:50 by haaghaja         ###   ########.fr       */
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





int	setup_redirection(t_command *cmd)
{
		int	i;
		int	fd;
		int	bfd;

		i = 0;
		bfd = dup(STDOUT_FILENO);
		while (i < cmd->files_count)
		{
			fd = open(cmd->output_files[i].arg, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd == -1)
				return (-1);
			i++;
			if (i == cmd->files_count)
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



int	exec_in_bg(t_command *cmd, t_shell *shell, int fd)
{
	pid_t	pid;
	int		bfd;



	bfd = -1;
	pid = fork();
	if (pid > 0)
	{
		add_job(shell, pid);
		printf("[%d] %d\n", get_job_id(shell->job_list, pid), pid);
	}
	if (pid == 0) // CHILD
	{
		if (fd != -1)
			dup2(fd, STDIN_FILENO);
		if (cmd->files_count != 0)
			bfd = setup_redirection(cmd);
		interpret_cmd_args(cmd, shell);
		if (is_builtin(cmd))
		{
			shell->exec_result = exec_builtin(cmd, shell);
		}
		else
		{
			shell->exec_result = exec_bin(cmd, shell);
		}
		restore_fd(bfd);
		exit(shell->exec_result);
	}
	
	return (0); //Change in the future
}

void exec_in_pipe(t_command *cmd, t_shell *shell, int in_fd, int out_fd)
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
		if (cmd->files_count != 0)
			bfd = setup_redirection(cmd);
		else
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
		}
		interpret_cmd_args(cmd, shell);
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
		if (in_fd != -1)
			close(in_fd);
		if (out_fd != -1)
			close(out_fd);
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

	interpret_cmd_args(cmd, shell);
	if (is_builtin(cmd))
	{
		if (cmd->files_count != 0)
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
			if (cmd->files_count != 0)
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
		}
		else if (cmd->oper == BG)
		{
			exec_in_bg(cmd, shell, prev_fd);
			close(prev_fd);
			prev_fd = -1;
		}
		else
		{
			exec_ordinary(cmd, shell, prev_fd);
			close(prev_fd);
			prev_fd = -1;
		}
		//printf("EXEC STATUS: %d\n", shell->exec_result);
		if (cmd->oper == AND && shell->exec_result != 0)
			cmd = cmd->next;
		if (cmd->oper == OR && shell->exec_result == 0)
			cmd = cmd->next;
		if (cmd)
			cmd = cmd->next;
	}
	return (shell->exec_result);
}
