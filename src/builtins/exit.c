/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:41:25 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/07 18:18:18 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* same behavior as in exit bash func */
int	safe_shell_exit(t_command *cmd, t_shell *shell)
{
	int	exit_code;

	printf("exit\n");
	if (cmd != NULL && cmd->argc > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (0);
	}
	exit_code = SUCCESS;
	if (cmd != NULL && cmd->argc == 2)
	{
		if (digits_only(cmd->argv[1]))
			exit_code = ft_atoi(cmd->argv[1]) % 256;
		else
		{
			printf("minishell: exit: %s: numeric argument required\n",
				cmd->argv[1]);
		}
	}
	rl_clear_history();
	free_env_list(shell);
	exit(exit_code);
}
/* do not forget to clean cmd & other data */
