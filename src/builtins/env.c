/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:58:34 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/28 15:26:32 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env_list(t_shell *shell)
{
	t_env	*list;

	list = shell->env_list;
	while (list)
	{
		printf("%s=%s\n", list->key, list->val);
		list = list->next;
	}
	return (SUCCESS);
}

