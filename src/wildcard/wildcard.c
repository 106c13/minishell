/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:37:47 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/07 18:10:29 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "minishell.h"

int	match_pattern(char *pattern, char *filename)
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

// when passing arg here it should 100 % be not quoted and contains * sign
char	**replace_wildcards(char *arg, char **argv)
{
	DIR				*dir;
	struct dirent	*entry;
	char			match_found;

	match_found = 0;
	dir = opendir(".");
	if (!dir)
		return (str_arr_append(argv, arg));
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] == '.' && arg[0] != '.')
			continue ;
		if (match_pattern(arg, entry->d_name))
		{
			argv = str_arr_append(argv, entry->d_name);
			match_found = 1;
		}
	}
	closedir(dir);
	if (!match_found)
		argv = str_arr_append(argv, arg);
	return (argv);
}
