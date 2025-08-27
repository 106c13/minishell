/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:25:16 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/12 19:04:11 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "minishell.h"
#include "defines.h"

static bool	is_flag(char *str, bool *flags)
{
	bool	tmp_flags[2];

	if (*str++ != '-' || !str)
		return (false);
	tmp_flags[0] = false;
	tmp_flags[1] = false;
	while (*str)
	{
		if (*str == 'n')
			tmp_flags[0] = true;
		else if (*str == 'e')
			tmp_flags[1] = true;
		else
			return (false);
		str++;
	}
	if (tmp_flags[0]) flags[0] = true;
	if (tmp_flags[1]) flags[1] = true;
	return (true);
}

static	void	print_escape(char *str)
{
	if (*str == 'n')
		write(STDOUT_FILENO, "\n", 1);
	else if (*str == 't')
		write(STDOUT_FILENO, "\t", 1);
	else if (*str == 'r')
		write(STDOUT_FILENO, "\r", 1);
	else if (*str == '\\')
		write(STDOUT_FILENO, "\\", 1);
	else
	{
		write(STDOUT_FILENO, "\\", 1);
		write(STDOUT_FILENO, str, 1);
	}
}

static	void	echo_print(char *str, bool *flags)
{
	while (*str)
	{
		if (*str == '\\' && flags[1])
			print_escape(++str);
        else
            write(STDOUT_FILENO, str, 1);
        str++;
	}
}

int	echo(t_ast *leaf)
{
	int	i;
	bool	flags[2]; // -n and -e

	i = 1;
	flags[0] = false;
	flags[1] = false;
	while (i < leaf->argc && is_flag(leaf->argv[i], flags))
		i++;
	while (i < leaf->argc)
	{
		echo_print(leaf->argv[i], flags);
		if (i < leaf->argc - 1)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!flags[0])
		write(STDOUT_FILENO, "\n", 1);
	return (SUCCESS);
}
