/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:45:04 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/30 17:50:52 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_bin_path(char *path, char *bin)
{
	char	*result;
	char	*tmp;

	result = ft_strjoin(path, "/");
	tmp = result;
	result = ft_strjoin(result, bin);
	free(tmp);
	return (result);
}

int	exec_bin(t_command *cmd, t_shell *shell)
{
	char	*path;
	char	**split_path;
	char	*bin;
	int		i;

	path = get_env_val(shell->env_list, "PATH");
	if (path == NULL)
		return (FAILURE);
	split_path = ft_split(path, ':');
	i = -1;
	while (split_path[++i])
	{
		bin = get_bin_path(split_path[i], cmd->cmd);
		// execve(bin, ):
		printf("possible path: %s\n", bin);
		free(bin);
	}
	free_split(split_path);
	printf("minishell: command not found: %s\n", cmd->cmd);
	return (SUCCESS);
}
