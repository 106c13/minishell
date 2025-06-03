/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:23:12 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/03 17:11:33 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_working_dir(t_command *cmd, t_shell *shell)
{
	char	*pwd;

	if (cmd->args_count != 1)
	{
		printf("pwd: too many arguments\n");
		return (FAILURE);
	}
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	(void)shell;
	return (SUCCESS);
}
