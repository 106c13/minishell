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

#include "minishell.h"

/* DEBUG */
void	print_env_list(t_shell *shell);

/*
 * Function that listens user's commads
 */
static void	listen(t_shell *shell)
{
	char	*cmd;
	char	*shell_prompt;

	shell_prompt = get_shell_prompt(shell);
	while (1)
	{
		cmd = readline(shell_prompt);
		if (!cmd) // Ctrl-D
			break ;
		// pass command to detecting func & execute
		add_history(cmd);
		free(cmd);
	}
	printf("exit\n");
	free(shell_prompt);
	(void)shell;
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	init_env_list(&shell, env);
	//print_env_list(&shell);
	setup_signals();
	listen(&shell);
	free_env_list(&shell);
	rl_clear_history();
	return ((void)argc, (void)argv, 0);
}
