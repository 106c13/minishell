/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:27:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/21 21:56:39 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

/*
 * Function that listens user's commads
 */
static void	listen(void)
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
}

/*
 * Function for environment initialization
 * Now just prints all given data
 */
static void	init_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	init_env(env);
	setup_signals();
	listen();
	rl_clear_history();
	return (0);
}
