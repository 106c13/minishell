/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:01:29 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/12 19:02:40 by azolotar         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (i == 0 && !(ft_isalpha(arg[i]) || arg[i] == '_'))
			return (0);
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	if (arg == NULL || arg[0] == '\0')
		return (0);
	return (1);
}

int	export_env(t_command *cmd, t_shell *shell)
{
	int		i;
	int		ret;

	ret = SUCCESS;
	if (cmd->argc == 1)
		return (print_export_env(shell->env_list), SUCCESS);
	i = 0;
	while (++i < cmd->argc)
	{
		if (is_valid_arg(cmd->argv[i]))
			update_or_add_env(cmd->argv[i], shell->env_list);
		else
		{
			ret = FAILURE;
			cmd->argv[i][strlen_till(cmd->argv[i], '=')] = '\0';
			printf("minishell: export: %s; not a valid identifier\n",
				cmd->argv[i]);
		}
	}
	return (ret);
}
