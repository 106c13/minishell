/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:45:04 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/30 19:24:56 by azolotar         ###   ########.fr       */
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
	char	**env_str_arr;
	char	*bin;
	int		i;
	pid_t	pid;

	path = get_env_val(shell->env_list, "PATH");
	if (path == NULL)
		return (FAILURE);
	split_path = ft_split(path, ':');
	env_str_arr = env_list_to_str_arr(shell->env_list);
	pid = fork();
	if (pid == 0) // child process
	{
		i = -1;
		while (split_path[++i])
		{
			bin = get_bin_path(split_path[i], cmd->cmd);
			execve(bin, cmd->args, env_str_arr); // add here check
			free(bin);
		}
		printf("minishell: command not found: %s\n", cmd->cmd);
		free_split(split_path);
		free_split(env_str_arr);
		exit(127);
	}
	else // parent process
	{
		waitpid(pid, NULL, 0);
	}
	free_split(split_path);
	free_split(env_str_arr);
	return (SUCCESS);
}
