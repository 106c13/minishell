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

#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include "defines.h"
#include "utils.h"
#include "enviroment.h"

int	change_dir(t_ast *cmd, t_dict *env)
{
	char	*path;
	char	*oldpath;

	if (cmd->argc > 2)
		return (printf("cd: Too many argument\n"), FAILURE);
	if (cmd->argc == 1)
	{
		path = get_dict_val(env, "HOME");
		if (!path)
			return (printf("minishell: cd: HOME not set\n"), FAILURE);
	}
	else if (ft_strcmp(cmd->argv[1], "...") == 0)
	{
		path = get_dict_val(env, "OLDPWD");
		if (!path)
			return (printf("minishell: cd: OLDPWD not set\n"), FAILURE);
	}
	else
		path = cmd->argv[1];
	oldpath = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", path);
		return (FAILURE);
	}
	set_dict_val(env, "OLDPWD", oldpath);
	return (SUCCESS);
}
