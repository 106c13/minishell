/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:01:29 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/29 19:10:55 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_or_add_env(char *arg, t_env *list)
{
	(void)arg;
	(void)list;
}

static int	is_valid_arg(char *arg)
{
	(void)arg;
	return (0);
}

int	export_env(t_command *cmd, t_shell *shell)
{
	int		args_count;
	int		i;

	args_count = get_args_count(cmd->args);
	if (args_count == 0)
		return (print_sorted_env(shell->env_list), SUCCESS);
	i = -1;
	while (++i < args_count)
	{
		if (is_valid_arg(cmd->args[i]))
			update_or_add_env(cmd->args[i], shell->env_list);
		else
			continue ;
	}
	return (SUCCESS);
}
