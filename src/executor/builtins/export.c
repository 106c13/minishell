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

#include <stdio.h>
#include <stdbool.h>
#include "minishell.h"
#include "enviroment.h"
#include "defines.h"
#include "utils.h"

bool	is_env_var(char *str)
{
	return (*str == '$' && (ft_isalnum(str[1]) || str[1] == '_' || str[1] == '?'));
}

bool	is_valid_identifier(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return (false);
	arg++;
	while (ft_isalnum(*arg) || *arg == '_')
		arg++;
	if (*arg == '+')
		arg++;
	if (*arg != '\0' && *arg != '=')
		return (false);
	return (true);
}

int	export_env(t_ast *cmd, t_dict *env)
{
	int		i;
	char	*key;
	char	*val;

	if (cmd->argc == 1)
		return (print_dict(env), SUCCESS);
	i = 0;
	while (++i < cmd->argc)
	{
		if (!is_valid_identifier(cmd->argv[i]))
			return (printf("minishell: export: `%s': not a valid identifier\n", cmd->argv[i]), FAILURE);
		key = cmd->argv[i];
		val = ft_strchr(cmd->argv[i], '=');
		if (val)
			*val++ = '\0';
		set_dict_val(env, key, val);
	}
	return (SUCCESS);
}
