/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:01:48 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/25 21:50:34 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"

void	set_exec_result(t_shell *shell, int status)
{
	shell->exec_result = 0;
	if (WIFEXITED(status))
		shell->exec_result = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exec_result = 128 + WTERMSIG(status);
	else
		shell->exec_result = status;
	if (shell->exec_result > 256)
		shell->exec_result /= 256;
}

void	do_in_ss(t_command **cmd, t_shell *shell)
{
	if (get_ss_next_operator(*cmd, shell, 0) == PIPE)
		run_ss_in_pipe(cmd, shell);
	else
		run_ss_ordinary(cmd, shell);
}

int	exec_cmd(t_command *cmd, t_shell *shell)
{
	if (is_multiple_file(cmd->args, cmd->args_count))
	{
		shell->exec_result = 1;
		return (printerr1("ambiguous redirect"), 1);
	}
	if (setup_redirection(cmd, shell) == FAILURE)
		return (FAILURE);
	if (!cmd->argv)
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

int	start_exec(t_command *cmd, t_shell *shell)
{
	while (cmd)
	{
		if (cmd->depth > shell->depth)
			do_in_ss(&cmd, shell);
		else if (cmd->depth == shell->depth)
		{
			expand_args(cmd, shell);
			if (cmd->op.type == PIPE && cmd->op.depth == shell->depth)
				start_pipe(cmd, shell);
			else
				exec_ordinary(cmd, shell);
		}
		else
			break ;
		if (!cmd || (cmd->last_in_group && shell->depth == cmd->depth)
			|| shell->exec_result == 130)
			break ;
		cmd = go_to_next_cmd(cmd, shell);
	}
	collect_finished_jobs(shell);
	return (shell->exec_result);
}
