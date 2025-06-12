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

#include "minishell.h"

static int	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(t_command *cmd, t_shell *shell)
{
	char	n_flag;
	int		i;
	int		first_arg;

	n_flag = 0;
	i = 1;
	while (i < cmd->argc && is_n_flag(cmd->argv[i]))
	{
		n_flag = 1;
		i++;
	}
	first_arg = 1;
	while (i < cmd->argc)
	{
		if (!first_arg)
			printf(" ");
		printf("%s", cmd->argv[i]);
		first_arg = 0;
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	(void)shell;
	return (SUCCESS);
}
