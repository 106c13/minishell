/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:45:04 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 18:48:04 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_local_bin(t_command *cmd, char **env_str_arr, t_shell *shell)
{
	(void)shell;
	if (access(cmd->cmd->str, F_OK) != 0)
	{
		free_split(env_str_arr);
		printerr2(cmd->cmd->str, "No such file or directory");
		return (127);
	}
	if (access(cmd->cmd->str, X_OK) != 0)
	{
		free_split(env_str_arr);
		printerr2(cmd->cmd->str, "Permission denied");
		return (126);
	}
	execve(cmd->cmd->str, cmd->argv, env_str_arr);
	free_split(env_str_arr);
	printerr2(cmd->cmd->str, "Execution failded");
	return (126);
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

char	*find_executable_path(t_command *cmd, t_shell *shell)
{
	struct stat	st;
	char		*path;
	char		**split_path;
	char		*full_path;
	int			i;

	path = get_env_val(shell->env_list, "PATH");
	if (path == NULL)
		return (printerr2(cmd->cmd->str, "PATH not set"), NULL);
	split_path = ft_split(path, ':');
	if (split_path == NULL)
		return (NULL);
	i = -1;
	while (split_path[++i])
	{
		full_path = get_bin_path(split_path[i], cmd->cmd->str);
		if (!full_path)
			continue ;
		if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode)
			&& access(full_path, X_OK) == 0)
			return (free_split(split_path), full_path);
		else
			free(full_path);
	}
	return (free_split(split_path), NULL);
}

static int	exec_path_bin(t_command *cmd, char **env_str_arr, t_shell *shell)
{
	char	*bin;
	int		exit_code;

	execve(cmd->cmd->str, cmd->argv, env_str_arr);
	bin = find_executable_path(cmd, shell);
	if (!bin)
	{
		free_split(env_str_arr);
		printerr2(cmd->cmd->str, "command not found");
		return (127);
	}
	execve(bin, cmd->argv, env_str_arr);
	free(bin);
	free_split(env_str_arr);
	if (errno == EACCES)
		exit_code = 126;
	else
		exit_code = 127;
	printerr2(cmd->cmd->str, strerror(errno));
	return (exit_code);
}

/* pid = 0 kid, pid > 0 parent */
int	exec_bin(t_command *cmd, t_shell *shell)
{
	char	**env_str_arr;

	env_str_arr = env_list_to_str_arr(shell->env_list);
	if (!env_str_arr)
		return (printerr2(cmd->cmd->str, "Failed to convert environment"),
			1);
	if (str_contains(cmd->cmd->str, '.') && str_contains(cmd->cmd->str, '/'))
		return (exec_local_bin(cmd, env_str_arr, shell));
	else
		return (exec_path_bin(cmd, env_str_arr, shell));
}
