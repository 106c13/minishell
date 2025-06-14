/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:51:52 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/14 15:07:19 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**append_split(char **argv, char *str)
{
	int		i;
	char	**split;

	split = ft_split(str, ' ');
	i = 0;
	while (split && split[i])
	{
		if (split[i][0] != '\0')
			argv = str_arr_append(argv, ft_strdup(split[i]));
		i++;
	}
	free_split(split);
	return (argv);
}

char	**expand_cmd_args(t_command *cmd, t_shell *shell)
{
	char	**argv;
	char	*str;
	int		i;
	t_arg	*arg;

	argv = NULL;
	i = -1;
	while (++i < cmd->args_count)
	{
		arg = &cmd->args[i];
		if (!arg->quoted && str_contains(arg->arg, '*'))
			argv = replace_wildcards(arg->arg, argv);
		else if (arg->interpet_env_var)
		{
			str = replace_env_vars(shell, arg->arg, arg->quoted);
			str = clear_quotes(str);
			if (!arg->quoted && str_contains(str, '*'))
				argv = replace_wildcards(str, argv);
			else if (cmd->args[i].quoted)
				argv = str_arr_append(argv, str);
			else
				argv = append_split(argv, str);
			free(str);
		}
		else
		{
			str = ft_strdup(cmd->args[i].arg);
			str = clear_quotes(str);
			argv = str_arr_append(argv, str);
			free(str);
		}
	}
	cmd->argv = argv;
	cmd->argc = get_args_count(argv);
	if (ft_strcmp(cmd->cmd->arg, cmd->argv[0]) != 0)
	{
		free(cmd->cmd->arg);
		cmd->cmd->arg = ft_strdup(cmd->argv[0]);
	}
	return (argv);
}
