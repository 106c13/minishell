/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:01:29 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/03 18:36:25 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_or_add_env(char *arg, t_env *list)
{
	char	**split;

	if (str_contains(arg, '='))
	{
		split = ft_split(arg, '=');
		if (get_args_count(split) != 2)
		{
			free_split(split);
			return ;
		}
		set_env_val(list, split[0], split[1]);
		free_split(split);
	}
	else
	{
		if (env_contains(list, arg))
			return ;
		else
			set_env_val(list, arg, NULL);
	}
}

static int	is_valid_arg(char *arg)
{
	(void)arg;
	return (1);
}

int	export_env(t_command *cmd, t_shell *shell)
{
	int		i;

	cmd->args += 1;
	if (cmd->args_count == 0)
		return (print_export_env(shell->env_list), SUCCESS);
	i = -1;
	while (++i < cmd->args_count)
	{
		if (is_valid_arg(cmd->args[i].arg))
			update_or_add_env(cmd->args[i].arg, shell->env_list);
		else
			continue ;
	}
	return (SUCCESS);
}
