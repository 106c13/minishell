/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:27:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/26 19:58:28 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function that listens user's commads
 */
static void	listen(t_shell *shell)
{
	char	*cmd;

	while (1)
	{
		cmd = readline("minishell > ");
		if (!cmd) // Ctrl-D
		{
			free(cmd);
			safe_shell_exit(shell);
		}
		if (cmd[0] != '\0')
		{
			// cmd_data = parse_cmd(shell); or someting like this
			exec_cmd(cmd, shell);
			add_history(cmd);
		}
		free(cmd);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	init_env_list(&shell, env);
	setup_signals();
	listen(&shell);
	return ((void)argc, (void)argv, 0);
}
