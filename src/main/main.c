/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:27:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/09/17 16:52:02 by haaghaja         ###   ########.fr       */
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
#include "expander.h"
#include "get_next_line.h"
#include "utils.h"

static void	init_session(t_shell *shell)
{
	int		fd;
	char	*line;
	t_token	*tokens;
	t_ast	*ast;

	fd = open(".minishellrc", O_RDONLY);
	if (fd == -1)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		//printf("LINE: %s", line);
		line[ft_strlen(line) - 1] = '\0';
		tokens = tokenize(line);
    	tokens = expand_aliases(tokens, shell->aliases);
		if (!check_token_array(tokens))
		{
			free(tokens);
			continue ;
		}
		ast = build_ast(tokens);
		if (ast)
			shell->exec_result = execute_node(ast, shell);
		free(line);
		free(ast);
		free(tokens);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	listen_shell(t_shell *shell)
{
	char	*input;
	char	*prompt;
	t_token	*tokens;
	t_ast	*ast;

	while (true)
	{
		prompt = get_prompt();
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			printf("\nexit\n");
			break ;
		}
		input = multiline_input(input);
		add_history(input);
		tokens = tokenize(input);
    	tokens = expand_aliases(tokens, shell->aliases);
		if (!check_token_array(tokens))
		{
			free(tokens);
			continue ;
		}
		ast = build_ast(tokens);
		free(input);
		free_tokens(tokens);
		//printf("\n");
		if (ast)
		{
			shell->exec_result = execute_node(ast, shell);
			free_ast(ast);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	/* In future add init_shell function */
	shell.aliases = NULL;
	shell.pid = getpid();
	init_env_list(&shell, env);
	init_session(&shell);
	listen_shell(&shell);
	return ((void)argc, (void)argv, shell.exec_result);
}
