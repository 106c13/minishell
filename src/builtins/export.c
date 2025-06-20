/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:01:29 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 15:13:25 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_or_add_env(char *arg, t_shell *shell)
{
	char	**split;
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		split = ft_split(arg, '=');
		if (!split || !split[0])
		{
			free_split(split);
			return ;
		}
		if (!split[1])
			set_env_val(shell->env_list, split[0], "");
		else
			set_env_val(shell->env_list, split[0], split[1]);
		free_split(split);
	}
	else
	{
		if (get_env_val(shell->env_list, arg) != NULL)
			return ;
		set_env_val(shell->env_list, arg, NULL);
	}
}

static int	is_valid_arg(char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (i == 0 && !(ft_isalpha(arg[i]) || arg[i] == '_'))
			return (0);
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	if (arg[i] == '=' && i == 0)
		return (0);
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
			update_or_add_env(cmd->argv[i], shell);
		else
		{
			ret = FAILURE;
			cmd->argv[i][strlen_till(cmd->argv[i], '=')] = '\0';
			printerr_three("export", cmd->argv[i], "not a valid identifier");
		}
	}
	return (ret);
}
