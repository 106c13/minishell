/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:27:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/22 23:22:26 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

/* DEBUG */
void	print_env_list(t_shell *shell);

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
			break ;
		// pass command to detecting func & execute
		add_history(cmd);
		free(cmd);
	}
	(void)shell;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	init_env_list(&shell, env);
	print_env_list(&shell);
	setup_signals();
	listen(&shell);
	free_env_list(&shell);
	rl_clear_history();
	return ((void)argc, (void)argv, 0);
}
