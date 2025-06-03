/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:28:08 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/03 18:33:58 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_pwds(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	set_env_val(shell->env_list, "PWD", new_pwd);
	set_env_val(shell->env_list, "OLDPWD", old_pwd);
	free(new_pwd);
}

int	change_dir(t_command *cmd, t_shell *shell)
{
	char	*path;
	int		args_count;
	char	*old_pwd;
	char	*tmp;

	cmd->args += 1;
	args_count = get_args_count(cmd->args);
	if (args_count == 1)
	{
		path = cmd->args[0];
		if (path[0] == '$')
		{
			tmp = get_env_val(shell->env_list, path + 1);
			if (tmp != NULL)
			{
				free(path);
				path = ft_strdup(tmp);
			}
			else
			{
				printf("minishell: cd: Not enough arguments\n");
				return (FAILURE);
			}
		}
		old_pwd = getcwd(NULL, 0);
		if (chdir(path) != 0)
		{
			free(old_pwd);
			printf("minishell: cd: %s: No such file or directory\n", path);
			return (FAILURE);
		}
		update_env_pwds(shell, old_pwd);
		free(old_pwd);
	}
	else
	{
		printf("minishell: cd: Wrong arguments count\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
