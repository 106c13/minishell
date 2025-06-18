/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:09:52 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/18 17:10:34 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup(t_shell *shell)
{
	// future: close fd in all cmds
	rl_clear_history();
	free_env_list(shell);
	free_cmd_list(shell->cmd_ptr);
}

void	free_cmd_list(t_command *cmd)
{
	t_command	*next;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->args)
			free_args(cmd->args, cmd->args_count);
		if (cmd->argv)
			free_split(cmd->argv);
		if (cmd->delimiter)
			free(cmd->delimiter);
		free(cmd);
		cmd = next;
	}
}
