/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:28:08 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/28 19:33:47 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_pwds(t_shell *shell)
{
	char	*curr_pwd;
	char	*new_pwd;

	curr_pwd = ft_strdup(get_env_val(shell->env_list, "PWD"));
	new_pwd = getcwd(NULL, 0);
	set_env_val(shell->env_list, "PWD", getcwd(NULL, 0));
	set_env_val(shell->env_list, "OLDPWD", curr_pwd);
}

int	change_dir(t_command *cmd, t_shell *shell)
{
	char	*path;
	int		args_count;

	args_count = get_args_count(cmd->args);
	if (args_count == 1)
	{
		path = cmd->args[0];
		if (chdir(path) != 0)
		{
			printf("minishell: cd: %s: No such file or directory\n", path);
			return (FAILURE);
		}
	}
	else
	{
		printf("minishell: cd: Wrong arguments count\n");
		return (FAILURE);
	}
	update_env_pwds(shell);
	return (SUCCESS);
}
