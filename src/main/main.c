/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:27:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/28 19:27:07 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Function that listens user's commads
 */
static void	listen(t_shell *shell)
{
	char		*input;
	t_command	*cmd;

	while (1)
	{
		input = readline("minishell > ");
		if (!input) // Ctrl-D
		{
			free(input);
			safe_shell_exit(shell);
		}
		if (input[0] != '\0')
		{
			add_history(input);
			cmd = parse_command(input);
			free(input);
			if (cmd == NULL) // give parsing error to user
				continue ;
			exec_cmd(cmd, shell);
		}
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
