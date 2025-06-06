/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:46:12 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/07 18:17:24 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *cmd)
{
	return (
		ft_strcmp(cmd->cmd->arg, "exit") == 0
		|| ft_strcmp(cmd->cmd->arg, "env") == 0
		|| ft_strcmp(cmd->cmd->arg, "unset") == 0
		|| ft_strcmp(cmd->cmd->arg, "export") == 0
		|| ft_strcmp(cmd->cmd->arg, "pwd") == 0
		|| ft_strcmp(cmd->cmd->arg, "cd") == 0
		|| ft_strcmp(cmd->cmd->arg, "echo") == 0
	);
}

int	exec_builtin(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->cmd->arg, "exit") == 0)
		return (safe_shell_exit(cmd, shell));
	if (ft_strcmp(cmd->cmd->arg, "env") == 0)
		return (print_env_list(cmd, shell));
	if (ft_strcmp(cmd->cmd->arg, "unset") == 0)
		return (unset_env(cmd, shell));
	if (ft_strcmp(cmd->cmd->arg, "export") == 0)
		return (export_env(cmd, shell));
	if (ft_strcmp(cmd->cmd->arg, "pwd") == 0)
		return (print_working_dir(cmd, shell));
	if (ft_strcmp(cmd->cmd->arg, "cd") == 0)
		return (change_dir(cmd, shell));
	if (ft_strcmp(cmd->cmd->arg, "echo") == 0)
		return (echo(cmd, shell));
	return (0);
}
