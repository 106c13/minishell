/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:25:16 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/03 17:16:52 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_command *cmd, t_shell *shell)
{
	char	n_flag;
	int		args_count;
	int		i;
	char	*tmp;

	(void)shell;
	cmd->args += 1;
	args_count = get_args_count(cmd->args);
	n_flag = 0;
	if (args_count >= 1 && ft_strcmp(cmd->args[0], "-n") == 0)
		n_flag = 1;
	i = n_flag;
	while (i < args_count)
	{
		if (cmd->args[i][0] == '$')
		{
			tmp = get_env_val(shell->env_list, cmd->args[i] + 1);
			if (tmp != NULL)
			{
				free(cmd->args[i]);
				cmd->args[i] = ft_strdup(tmp);
			}
		}
		printf("%s", cmd->args[i]);
		if (i < (args_count - 1))
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (SUCCESS);
}
