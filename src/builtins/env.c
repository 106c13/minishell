/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:58:34 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/07 18:21:22 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env_list(t_command *cmd, t_shell *shell)
{
	t_env	*list;

	if (cmd->argc != 1)
	{
		printf("env: too many arguments\n");
		return (FAILURE);
	}
	list = shell->env_list;
	while (list)
	{
		if (list->val != NULL)
			printf("%s=%s\n", list->key, list->val);
		list = list->next;
	}
	return (SUCCESS);
}
