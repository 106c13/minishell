/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 15:28:08 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/28 15:53:17 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_pwds(t_shell *shell)
{
	char	*curr_pwd;

	curr_pwd = get_env_val(shell->env_list, "PWD");
	set_env_val(shell->env_list, "PWD", getcwd(NULL, 0));
	set_env_val(shell->env_list, "OLDPWD", curr_pwd);
}

int	change_dir(t_command *cmd, t_shell *shell)
{
	char	*path;

	path = cmd->args[0];
	if (!path)
		return (FAILURE);
	// handle -
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (FAILURE);
	}
	update_env_pwds(shell);
	return (SUCCESS);
}
