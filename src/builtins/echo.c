/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:25:16 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/03 18:34:20 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_command *cmd, t_shell *shell)
{
	printf("UPDATE ECHO\n");
	return (SUCCESS);
	/*
	char	n_flag;
	int		args_count;
	int		i;

	(void)shell;
	cmd->args += 1;
	args_count = get_args_count(cmd->args);
	n_flag = 0;
	if (args_count >= 1 && ft_strcmp(cmd->args[0], "-n") == 0)
		n_flag = 1;
	i = n_flag;
	while (i < args_count)
	{
		printf("%s", cmd->args[i]);
		if (i < (args_count - 1))
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (SUCCESS);
	*/
}
