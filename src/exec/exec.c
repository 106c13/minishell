/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:18:17 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/05 20:22:01 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_in_bg(t_command *cmd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
		printf("[ADD JOB NUMBER] %d\n", pid);
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


int	exec_cmd(t_command *cmd, t_shell *shell)
{
	while (cmd)
	{
		if (cmd->oper == BG)
		{
			exec_in_bg(cmd, shell);
			cmd = cmd->next;
			continue;
		}
		interpret_cmd_args(cmd, shell);
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
		cmd = cmd->next;
	}
	return (shell->exec_result);
}
