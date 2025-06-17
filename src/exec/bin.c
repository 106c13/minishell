/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:45:04 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/17 16:59:55 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_exit(t_command *cmd, char *msg, int code, t_shell *shell)
{
	printerr_two(cmd->cmd->str, msg);
	rl_clear_history();
	free_env_list(shell);
	free_cmd_list(cmd);
	exit(code);
}

static void	exec_local_bin(t_command *cmd, char **env_str_arr, t_shell *shell)
{
	if (access(cmd->cmd->str, F_OK) != 0)
	{
		free_split(env_str_arr);
		print_error_exit(cmd, "No such file or directory", 127, shell);
	}
	if (access(cmd->cmd->str, X_OK) != 0)
	{
		free_split(env_str_arr);
		print_error_exit(cmd, "Permission denied", 126, shell);
	}
	execve(cmd->cmd->str, cmd->argv, env_str_arr);
	free_split(env_str_arr);
	print_error_exit(cmd, "Execution failded", 126, shell);
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
		print_error_exit(cmd, "PATH not set", 127, shell);
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
	free_split(split_path);
	return (NULL);
}

static void	exec_path_bin(t_command *cmd, char **env_str_arr, t_shell *shell)
{
	char	*bin;
	int		exit_code;

	bin = find_executable_path(cmd, shell);
	if (!bin)
	{
		free_split(env_str_arr);
		print_error_exit(cmd, "command not found", 127, shell);
	}
	execve(bin, cmd->argv, env_str_arr);
	free(bin);
	free_split(env_str_arr);
	if (errno == EACCES)
		exit_code = 126;
	else
		exit_code = 127;
	print_error_exit(cmd, strerror(errno), exit_code, shell);
}

/* pid = 0 kid, pid > 0 parent */
int	exec_bin(t_command *cmd, t_shell *shell)
{
	char	**env_str_arr;

	env_str_arr = env_list_to_str_arr(shell->env_list);
	if (!env_str_arr)
		print_error_exit(cmd, "Failed to convert environment", 1, shell);
	if (str_contains(cmd->cmd->str, '/'))
		exec_local_bin(cmd, env_str_arr, shell);
	else
		exec_path_bin(cmd, env_str_arr, shell);
	return (SUCCESS);
}
