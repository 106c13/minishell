/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:18:17 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/27 18:17:25 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(char *cmd, t_shell *shell)
{
	if (is_builtin(cmd))
	{
		shell->exec_result = exec_builtin(cmd, shell);
	}
	else
	{
		shell->exec_result = exec_bin(cmd, shell);
	}

	if (!shell->exec_result)
	{
		printf("minishell: command not found: %s\n", cmd);
	}
	return (0);
}
