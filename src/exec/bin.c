/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:45:04 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/27 18:25:47 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_bin(char *cmd, t_shell *shell)
{
	char	*path;
	char	**split_path;

	path = get_env_val(shell->env_list, "PATH");
	split_path = ft_split(path, ':');
	free_split(split_path);
	(void)cmd;
	(void)shell;
	return (0);
}
