/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:28:08 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 12:44:48 by azolotar         ###   ########.fr       */
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
	char	*old_pwd;

	if (cmd->argc == 1)
		return (printerr2("cd", "Wrong arguments count"),
			FAILURE);
	if (cmd->argc > 2)
		return (printerr2("cd", "too many arguments"),
			FAILURE);
	path = cmd->argv[1];
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		printerr3("cd", path, "No such file or directory");
		return (free(old_pwd), FAILURE);
	}
	update_env_pwds(shell, old_pwd);
	return (free(old_pwd), SUCCESS);
}
