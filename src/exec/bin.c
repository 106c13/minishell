/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:45:04 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/31 21:17:50 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_bin_path(char *path, char *bin)
{
	char	*result;
	char	*tmp;

	result = ft_strjoin(path, "/");
	tmp = result;
	result = ft_strjoin(result, bin);
	free(tmp);
	return (result);
}

static void	print_error_exit(char *cmd, char *msg, int code)
{
	printf("minishell: %s: %s\n", cmd, msg);
	exit(code);
}

static void	exec_local_bin(t_command *cmd, char **env_str_arr)
{
	if (access(cmd->cmd, F_OK) != 0)
	{
		free_split(env_str_arr);
		print_error_exit(cmd->cmd, "No such file or directory", 127);
	}
	if (access(cmd->cmd, X_OK) != 0)
	{
		free_split(env_str_arr);
		print_error_exit(cmd->cmd, "Permission denied", 126);
	}
	execve(cmd->cmd, cmd->args, env_str_arr);
	free_split(env_str_arr);
	print_error_exit(cmd->cmd, "Execution failded", 126);
}

static void	exec_path_bin(t_command *cmd, char **env_str_arr, t_shell *shell)
{
	char	*path;
	char	**split_path;
	char	*bin;
	int		i;

	path = get_env_val(shell->env_list, "PATH");
	if (path == NULL)
	{
		free_split(env_str_arr);
		print_error_exit(cmd->cmd, "PATH not set", 127);
	}
	split_path = ft_split(path, ':');
	if (!split_path)
	{
		free_split(env_str_arr);
		print_error_exit("minishell", "Malloc failed", 1);
	}
	i = -1;
	while (split_path[++i])
	{
		bin = get_bin_path(split_path[i], cmd->cmd);
		if (!bin)
			continue ;
		if (access(bin, X_OK) == 0)
		{
			execve(bin, cmd->args, env_str_arr);
			free(bin);
			break ;
		}
		free(bin);
	}
	free_split(split_path);
	free_split(env_str_arr);
	print_error_exit(cmd->cmd, "command not found", 127);
}

int	exec_bin(t_command *cmd, t_shell *shell)
{
	char	**env_str_arr;
	pid_t	pid;

	pid = fork();
	if (pid == 0) /* CHILD PROCESS */
	{
		env_str_arr = env_list_to_str_arr(shell->env_list);
		if (!env_str_arr)
		{
			print_error_exit("minishell", "Failed to convert environment", 1);
		}
		if (str_contains(cmd->cmd, '/'))
		{
			exec_local_bin(cmd, env_str_arr);
		}
		else
		{
			exec_path_bin(cmd, env_str_arr, shell);
		}
	}
	else if (pid > 0) /* PARENT PROCESS */
	{
		waitpid(pid, NULL, 0);
	}
	else /* FORK ERROR */
	{
	}
	return (SUCCESS);
}
