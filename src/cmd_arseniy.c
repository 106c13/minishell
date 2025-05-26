/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arseniy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:18:17 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/26 19:23:12 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	check_builtins(char *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd, "exit") == 0)
		return (safe_shell_exit(shell), 1);
	if (ft_strcmp(cmd, "env") == 0)
		return (print_env_list(shell), 1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	return (0);
}

static int	check_bins(char *cmd, t_shell *shell)
{
	struct stat	file;

	(void)file;
	(void)cmd;
	(void)shell;
	return (0);
}

int	exec_cmd(char *cmd, t_shell *shell)
{
	if (check_builtins(cmd, shell) == 1)
		return (1);
	if (check_bins(cmd, shell) == 1)
		return (1);
	printf("minishell: command not found: %s\n", cmd);
	return (0);
}
