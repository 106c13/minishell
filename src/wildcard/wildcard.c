/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:37:47 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/07 17:06:20 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "minishell.h"

char	**str_arr_append(char **arr, char *str)
{
	char	**new_arr;
	int		len;
	int		i;

	if (arr == NULL)
		len = 0;
	else
		len = get_args_count(arr);
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (arr);
	i = 0;
	while (i < len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	if (arr != NULL)
		free(arr);
	new_arr[i++] = ft_strdup(str);
	new_arr[i] = NULL;
	return (new_arr);
}

static int	match_pattern(char *pattern, char *filename)
{
	if (*pattern == '\0' && *filename == '\0')
		return (1);
	if (*pattern == '*')
	{
		while (*pattern == '*')
			pattern++;
		if (*pattern == '\0')
			return (1);
		while (*filename)
		{
			if (match_pattern(pattern, filename))
				return (1);
			filename++;
		}
		return (0);
	}
	else if (*pattern == *filename)
		return (match_pattern(pattern + 1, filename + 1));
	else
		return (0);
}

void	replace_wildcards(t_command *cmd)
{
	int				i;
	DIR				*dir;
	struct dirent	*entry;
	char			**new_argv;

	i = -1;
	new_argv = NULL;
	while (cmd->argv[++i])
	{
		// cmd name
		if (i == 0 || !str_contains(cmd->argv[i], '*'))
		{
			new_argv = str_arr_append(new_argv, cmd->argv[i]);
			continue ;
		}
		dir = opendir(".");
		if (!dir)
			continue ;
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_name[0] == '.' && cmd->argv[i][0] != '.')
				continue ;
			if (match_pattern(cmd->argv[i], entry->d_name))
				new_argv = str_arr_append(new_argv, entry->d_name);
		}
		closedir(dir);
	}
	if (new_argv != NULL)
	{
		free_split(cmd->argv);
		cmd->argv = new_argv;
		cmd->argc = get_args_count(cmd->argv);
	}
}
