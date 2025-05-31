/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:18:17 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/31 20:13:38 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_command *cmd, t_shell *shell)
{
	if (is_builtin(cmd))
	{
		shell->exec_result = exec_builtin(cmd, shell);
	}
	else
	{
		shell->exec_result = exec_bin(cmd, shell);
	}
	return (shell->exec_result);
}
