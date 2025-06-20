/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:37:47 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 18:35:47 by haaghaja         ###   ########.fr       */
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

static t_arg	i_hate_norminette1(t_arg *parg)
{
	t_arg	why_25_lines;

	why_25_lines.str = NULL;
	why_25_lines.interpret_env_var = 0;
	why_25_lines.quoted = 0;
	why_25_lines.file = parg->file;
	why_25_lines.append = parg->append;
	why_25_lines.depth = parg->depth;
	why_25_lines.wed = 1;
	return (why_25_lines);
}

/* mf = match_found */
static t_arg	*i_hate_norminette2(t_arg *parg, t_arg *arr, int *len, int *mf)
{
	DIR				*dir;
	t_arg			new;
	struct dirent	*entry;

	*mf = 0;
	dir = opendir(".");
	if (dir == NULL)
		return (arr);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		if (entry->d_name[0] == '.' && parg->str[0] != '.')
			continue ;
		if (match_pattern(parg->str, entry->d_name))
		{
			new = i_hate_norminette1(parg);
			new.str = ft_strdup(entry->d_name);
			arr = append_arg(new, arr, len);
			*mf = 1;
		}
	}
	closedir(dir);
	return (arr);
}

/* parg = pattern_arg */
t_arg	*replace_wildcards(t_arg *parg, t_arg *arr, int *len)
{
	int		match_found;
	t_arg	new;

	arr = i_hate_norminette2(parg, arr, len, &match_found);
	if (!match_found)
	{
		parg->interpret_env_var = 0;
		parg->quoted = 0;
		new = i_hate_norminette1(parg);
		new.str = ft_strdup(parg->str);
		return (append_arg(new, arr, len));
	}
	return (arr);
}
