/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:45:04 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/04 20:03:24 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_exit(char *cmd, char *msg, int code)
{
	printf("minishell: %s: %s\n", cmd, msg);
	exit(code);
}

static void	exec_local_bin(t_command *cmd, char **env_str_arr)
{
	if (access(cmd->cmd->arg, F_OK) != 0)
	{
		free_split(env_str_arr);
		print_error_exit(cmd->cmd->arg, "No such file or directory", 127);
	}
	if (access(cmd->cmd->arg, X_OK) != 0)
	{
		free_split(env_str_arr);
		print_error_exit(cmd->cmd->arg, "Permission denied", 126);
	}
	execve(cmd->cmd->arg, cmd->argv, env_str_arr);
	free_split(env_str_arr);
	print_error_exit(cmd->cmd->arg, "Execution failded", 126);
}

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

char	*find_executable_path(char *cmd, t_shell *shell)
{
	struct stat	st;
	char		*path;
	char		**split_path;
	char		*full_path;
	int			i;

	path = get_env_val(shell->env_list, "PATH");
	if (path == NULL)
		print_error_exit(cmd, "PATH not set", 127);
	split_path = ft_split(path, ':');
	if (split_path == NULL)
		return (NULL);
	i = -1;
	while (split_path[++i])
	{
		full_path = get_bin_path(split_path[i], cmd);
		if (!full_path)
			continue ;
		if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) && access(full_path, X_OK) == 0)
		{
			free_split(split_path);
			return (full_path);
		}
		else
		{
			free(full_path);
		}
	}
	free_split(split_path);
	return (NULL);
}

static void	exec_path_bin(t_command *cmd, char **env_str_arr, t_shell *shell)
{
	char	*bin;
	int		exit_code;

	bin = find_executable_path(cmd->cmd->arg, shell);
	if (!bin)
	{
		free_split(env_str_arr);
		print_error_exit(cmd->cmd->arg, "command not found", 127);
	}
	execve(bin, cmd->argv, env_str_arr);
	free(bin);
	free_split(env_str_arr);
	if (errno == EACCES)
		exit_code = 126;
	else
		exit_code = 127;
	print_error_exit(cmd->cmd->arg, strerror(errno), exit_code);
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
		if (str_contains(cmd->cmd->arg, '/'))
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
