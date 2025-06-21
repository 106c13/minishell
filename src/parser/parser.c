/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:27 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/21 18:36:35 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_oper(t_oper	*op)
{


	if (op->type == PIPE)


		printf("%-2s", "|");


	else if (op->type == 12)


		printf("%-2s", "&");


	else if (op->type == 13)


		printf("%-2s", "||");


	else if (op->type == 14)


		printf("%-2s", "&&");


	else


		printf("%-2s", "");


	printf(" %-9d", op->depth);


}


void print_cmd(t_command *cmd)


{


	int i;


	int first_arg;


	printf("\n\033[1;34m%-20s %-8s %-15s %-15s %s\033[0m\n", "COMMAND", "DEPTH", "DELIMITER", "OPERATOR", "ARGS");


	printf("-----------------------------------------------------------------------------------------\n");





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


		if (cmd->delimiters)


			printf("%d %-15s ", cmd->delimiter_count, cmd->delimiters[0]);


		else


			printf("%-17s ",  "");





		


		print_oper(&cmd->op);


		// ARGS


		first_arg = 1;


		for (i = 0; i < cmd->args_count; i++) // Skip cmd->cmd


		{


			if (!first_arg)


				printf("%-20s %-7s %-31s ", "", "", "");


			else


				printf(" ");


				





			if (cmd->args[i].quoted)


				printf("\033[1;31m"); // Red


			if (cmd->args[i].interpret_env_var)


				printf("\033[1;32m"); // Green





			if (cmd->args[i].file == 2 && cmd->args[i].append)


				printf("OUTPUT %d: %s\033[0m %d APPEND", i, cmd->args[i].str, cmd->args[i].depth);


			else if (cmd->args[i].file == 2)


				printf("OUTPUT %d: %s\033[0m %d", i, cmd->args[i].str, cmd->args[i].depth);


			else if (cmd->args[i].file == 1)


				printf("INPUT %d: %s\033[0m %d", i, cmd->args[i].str, cmd->args[i].file);


			else


				printf("ARG %d: %s\033[0m %d", i, cmd->args[i].str, cmd->args[i].depth);





			if (cmd->args[i].quoted)


				printf(" \033[1;34mquoted\033[0m");





			printf("\n");


			first_arg = 0;


		}





		if (cmd->args_count <= 1)


			printf("\n");





		cmd = cmd->next;


	}


	printf("-----------------------------------------------------------------------------------------\n\n");


}

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

void	get_command(t_command *cmd, char *input)
{
	t_command	*tmp;
	char		*t_input;

	t_input = input;
	while (*input)
	{
		if (shell_split(&input, t_input, cmd) != 0)
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
	if (!*input)
		return (NULL);
	cmd = create_command();
	get_command(cmd, input);
	if (!cmd)
		return (NULL);
//    print_cmd(cmd);
	return (cmd);
}
