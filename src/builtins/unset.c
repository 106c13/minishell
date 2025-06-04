/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:39:10 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/04 21:01:16 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_env(t_command *cmd, t_shell *shell)
{
	int	i;

	if (cmd->argc == 1)
	{
		printf("unset: not enough arguments\n");
		return (FAILURE);
	}
	i = 1;
	while (cmd->argv[i] != NULL)
	{
		del_env_pair(&shell->env_list, cmd->argv[i]);
		i++;
	}
	return (SUCCESS);
}
