/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:01:29 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 16:13:09 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_plus_equal_env(char *arg, t_shell *shell)
{
	char	*key;
	char	*val;
	char	*existing;
	char	*joined;
	char	*plus;

	plus = ft_strchr(arg, '+');
	if (!plus || plus[1] != '=')
		return ;
	key = ft_substr(arg, 0, plus - arg);
	val = ft_strdup(plus + 2);
	if (!key || !val)
		return ;
	existing = get_env_val(shell->env_list, key);
	if (existing)
		joined = ft_strjoin(existing, val);
	else
		joined = ft_strdup(val);
	set_env_val(shell->env_list, key, joined);
	free(key);
	free(val);
	free(joined);
}

static int	update_or_add_env(char *arg, t_shell *shell)
{
	char	**split;
	char	*equal_pos;

	if (ft_strchr(arg, '+') && ft_strchr(arg, '+')[1] == '=')
		return (handle_plus_equal_env(arg, shell), 0);
	equal_pos = ft_strchr(arg, '=');
	if (equal_pos)
	{
		split = ft_split(arg, '=');
		if (!split || !split[0])
			return (free_split(split), 0);
		if (!split[1])
			set_env_val(shell->env_list, split[0], "");
		else
			set_env_val(shell->env_list, split[0], split[1]);
		free_split(split);
	}
	else
	{
		if (get_env_val(shell->env_list, arg) != NULL)
			return (0);
		set_env_val(shell->env_list, arg, NULL);
	}
	return (0);
}

static int	is_valid_arg(char *arg)
{
	int		i;

	if (!arg || !*arg)
		return (0);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=' && !(arg[i] == '+' && arg[i + 1] == '='))
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
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
			printerr_three("export", cmd->argv[i], "not a valid identifier");
		}
	}
	return (ret);
}
