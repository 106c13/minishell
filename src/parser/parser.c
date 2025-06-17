/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:27 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/17 19:29:13 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ONLY for tests
void	print_oper(int	oper)
{
	if (oper == 11)
		printf("%-15s", "|");
	else if (oper == 12)
		printf("%-15s", "&");
	else if (oper == 13)
		printf("%-15s", "||");
	else if (oper == 14)
		printf("%-15s", "&&");
	else
		printf("%-15s", "");
}
void print_cmd(t_command *cmd)
{
	int i;
	int first_arg;

	printf("\n\033[1;34m%-20s %-8s %-15s %-15s %s\033[0m\n", "COMMAND", "DEPTH", "DELIMITER", "OPERATOR", "ARGS");
	printf("--------------------------------------------------------------------------\n");

	while (cmd)
	{
		// COMMAND
		printf("%-20s ", cmd->cmd ? cmd->cmd->str : "(null)");

		// DEPTH
		if (cmd->last_in_group)
			printf("\033[1;31m");
		printf("%-8d ", cmd->depth);
		printf("\033[0m");

		// DELIMITER
		if (cmd->delimiter)
			printf("%-15s ", cmd->delimiter);
		else
			printf("%-15s ",  "");

		
		print_oper(cmd->operator_type);
		// ARGS
		first_arg = 1;
		for (i = 0; i < cmd->args_count; i++) // Skip cmd->cmd
		{
			if (!first_arg)
				printf("%-20s %-8s %-31s ", "", "", "");
			else
				printf(" ");
				

			if (cmd->args[i].quoted)
				printf("\033[1;31m"); // Red
			else if (cmd->args[i].interpret_env_var)
				printf("\033[1;32m"); // Green

			if (cmd->args[i].file == 2 && cmd->args[i].append)
				printf("OUTPUT %d: %s\033[0m %p APPEND", i, cmd->args[i].str, cmd->args[i].str);
			else if (cmd->args[i].file == 2)
				printf("OUTPUT %d: %s\033[0m %p", i, cmd->args[i].str, cmd->args[i].str);
			else if (cmd->args[i].file == 1)
				printf("INPUT %d: %s\033[0m %p", i, cmd->args[i].str, cmd->args[i].str);
			else
				printf("ARG %d: %s\033[0m %p", i, cmd->args[i].str, cmd->args[i].str);

			if (cmd->args[i].quoted)
				printf(" \033[1;34mquoted\033[0m");

			printf("\n");
			first_arg = 0;
		}

		if (cmd->args_count <= 1)
			printf("\n");

		cmd = cmd->next;
	}
	printf("--------------------------------------------------------------------------\n\n");
}

// ============================

int	calculate_depth(char *src, char *dest)
{
	int	depth;

	depth = 0;
	while (src != dest)
	{
		if (*src == '(')
			depth++;
		else if (*src == ')')
			depth--;
		src++;
	}
	return (depth);
}

void	get_command(t_command *cmd, char	*input)
{
	t_command	*tmp;
	char		*t_input;

	t_input = input;
	while (*input)
	{
		if (shell_split(&input, cmd) != 0)
			return ;
		if (*input)
		{
			tmp = cmd;
			cmd = create_command();
			tmp->next = cmd;
			cmd->depth = calculate_depth(t_input, input);
		}
	}
}

t_command	*parse_command(char *input)
{
	t_command	*cmd;

	input = trim_spaces(input);
	if (!*input || validate(input) != 0)
		return (NULL);
	cmd = create_command();
	get_command(cmd, input);
	if (!cmd)
		return (NULL);
	
	//print_cmd(cmd);
	return (cmd);
}
