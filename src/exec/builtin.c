/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:46:12 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/02 17:29:46 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_command *cmd)
{
	return (
		ft_strcmp(cmd->cmd, "exit") == 0 ||
		ft_strcmp(cmd->cmd, "env") == 0 ||
		ft_strcmp(cmd->cmd, "unset") == 0 ||
		ft_strcmp(cmd->cmd, "export") == 0 ||
		ft_strcmp(cmd->cmd , "pwd") == 0 ||
		ft_strcmp(cmd->cmd, "cd") == 0 ||
		ft_strcmp(cmd->cmd, "echo") == 0
	);
}

int	exec_builtin(t_command *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->cmd, "exit") == 0)
		return (safe_shell_exit(shell));
	if (ft_strcmp(cmd->cmd, "env") == 0)
		return (print_env_list(shell));
	if (ft_strcmp(cmd->cmd, "unset") == 0)
		return (unset_env(cmd, shell));
	if (ft_strcmp(cmd->cmd, "export") == 0)
		return (export_env(cmd, shell));
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		return (print_working_dir(shell));
	if (ft_strcmp(cmd->cmd, "cd") == 0)
		return (change_dir(cmd, shell));
	if (ft_strcmp(cmd->cmd, "echo") == 0)
		return (echo(cmd, shell));
	return (0);
}
