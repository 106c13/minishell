/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:39:10 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/03 18:37:16 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_env(t_command *cmd, t_shell *shell)
{
	printf("UPDATE UNSET\n");
	return (SUCCESS);
	/*
	int	args_count;
	int	i;

	cmd->args += 1;
	args_count = get_args_count(cmd->args);
	if (args_count == 0)
	{
		printf("unset: not enough arguments\n");
		return (FAILURE);
	}
	i = -1;
	while (cmd->args[++i] != NULL)
	{
		del_env_pair(&shell->env_list, cmd->args[i]);
	}
	return (SUCCESS);
	*/
}
