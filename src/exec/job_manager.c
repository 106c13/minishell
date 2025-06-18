/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:56:46 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/18 15:30:19 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	collect_finished_jobs(t_shell *shell)
{
	t_job	*curr;
	t_job	*prev;
	t_job	*next;
	int		status;
	pid_t	result;

	curr = shell->job_list;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		result = waitpid(curr->pid, &status, 0);
		set_exec_result(shell, status);
		if (result > 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->job_list = curr->next;
			free(curr);
		}
		else
			prev = curr;
		curr = next;
	}
}

t_job	*create_job(pid_t pid, int id)
{
	t_job	*job;

	job = malloc(sizeof(t_job));
	if (!job)
		return (NULL);
	job->id = id + 1;
	job->pid = pid;
	job->command = NULL;
	job->next = NULL;
	return (job);
}

void	add_job(t_shell *shell, pid_t pid)
{
	t_job	*job;

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
