/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:28:08 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/07 18:27:49 by azolotar         ###   ########.fr       */
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

	if (cmd->argc != 2)
		return (printf("minishell: cd: Wrong arguments count\n"),
			FAILURE);
	path = cmd->argv[1];
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (free(old_pwd), FAILURE);
	}
	update_env_pwds(shell, old_pwd);
	return (free(old_pwd), SUCCESS);
}
