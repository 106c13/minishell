/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:27:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/27 16:49:36 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <stdlib.h>
#include "minishell.h"
#include "parser.h"
#include "tokenizer.h"
#include "exec.h"
#include "enviroment.h"
#include "utils.h"

char *read_block(void)
{
	char	*line;
	char	*block;
	char	*tmp;

	block = NULL;
	while (true)
	{
		if (!block)
			line = readline("\033[38;5;196mminishell42? \033[0m");
		else
			line = readline("");
		if (!line)
			break;
		if (!*line)
			return (free(line), block);
		if (!block)
			block = ft_strdup(line);
		else
		{
			tmp = ft_strjoin(block, "\n");
			free(block);
			block = ft_strjoin(tmp, line);
			free(tmp);
		}
		free(line);
	}
	return (block);
}


static void	listen_shell(t_shell *shell)
{
	char	*input;
	t_token	*tokens;
	t_ast	*ast;

	while (true)
	{
		input = readline("\033[38;5;196mminishell42? \033[0m");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		add_history(input);
		tokens = tokenize(input);
		ast = build_ast(tokens);
		free(input);
		printf("\n");
		if (ast)
			shell->exec_result = execute_node(ast, shell);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	/* In future add init_shell function */
	init_env_list(&shell, env);
	shell.aliases = NULL;
	shell.pid = getpid();
	listen_shell(&shell);
	return ((void)argc, (void)argv, shell.exec_result);
}
