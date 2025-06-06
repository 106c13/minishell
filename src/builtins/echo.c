/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:25:16 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/04 20:52:57 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_command *cmd, t_shell *shell)
{
	char	n_flag;
	int		i;

	n_flag = 0;
	if (cmd->argc >= 2 && ft_strcmp(cmd->argv[1], "-n") == 0)
		n_flag = 1;
	i = n_flag + 1;
	while (i < cmd->argc)
	{
		printf("%s", cmd->argv[i]);
		if (i < (cmd->argc - 1))
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	(void)shell;
	return (SUCCESS);
}
