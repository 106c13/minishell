/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:25:16 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/03 20:03:18 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_command *cmd, t_shell *shell)
{
	char	n_flag;
	int		i;
	char	*tmp;

	(void)shell;
	cmd->args += 1;
	n_flag = 0;
	if (cmd->args_count >= 1 && ft_strcmp(cmd->args[0].arg, "-n") == 0)
		n_flag = 1;
	i = n_flag;
	while (i < cmd->args_count)
	{
		if (cmd->args[i].arg[0] == '$')
		{
			tmp = get_env_val(shell->env_list, cmd->args[i].arg + 1);
			if (tmp != NULL)
			{
				free(cmd->args[i].arg);
				cmd->args[i].arg = ft_strdup(tmp);
			}
		}
		printf("%s", cmd->args[i].arg);
		if (i < (cmd->args_count - 1))
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (SUCCESS);
}
