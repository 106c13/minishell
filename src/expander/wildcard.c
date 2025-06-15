/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:37:47 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/15 16:05:45 by azolotar         ###   ########.fr       */
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
t_arg	*replace_wildcards(t_arg *pattern_arg, t_arg *arr, int *len)
{
	DIR				*dir;
	struct dirent	*entry;
	char			match_found;
	t_arg			new;

	match_found = 0;
	dir = opendir(".");
	while (dir && 1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] == '.' && pattern_arg->str[0] != '.')
			continue ;
		if (match_pattern(pattern_arg->str, entry->d_name))
		{
			new.str = ft_strdup(entry->d_name);
			new.interpret_env_var = 0;
			new.quoted = 0;
			new.file = pattern_arg->file;
			new.append = pattern_arg->append;
			arr = append_arg(new, arr, len);
			match_found = 1;
		}
	}
	if (dir)
		closedir(dir);
	if (!match_found)
	{
		new.str = ft_strdup(pattern_arg->str);
		new.interpret_env_var = pattern_arg->interpret_env_var;
		new.quoted = pattern_arg->quoted;
		new.file = pattern_arg->file;
		new.append = pattern_arg->append;
		return (append_arg(new, arr, len));
	}
	return (arr);
}
