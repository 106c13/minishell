/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:27 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/15 18:50:55 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ONLY for tests
void	print_oper(int	oper)
{
	if (oper == 11)
		printf("OPERATOR: |\n");
	if (oper == 12)
		printf("OPERATOR: &\n");
	if (oper == 13)
		printf("OPERATOR: ||\n");
	if (oper == 14)
		printf("OPERATOR: &&\n");
}

void	print_cmd(t_command *cmd)
{
	int	i;

	printf("---------------cmd---------------\n");
	while (cmd)
	{
		printf("COMMAND: %s\n", cmd->cmd->str);
		i = 0;
		if (cmd->args)
		{
			while (i < cmd->args_count)
			{
				if (cmd->args[i].file == 2 && cmd->args[i].append)
					printf("OUTPUT %d: %s\033[0m APPEND", i, cmd->args[i].str);
				else if (cmd->args[i].file == 2)
					printf("OUTPUT %d: %s\033[0m", i, cmd->args[i].str);
				else if (cmd->args[i].file == 1)
					printf("INPUT %d: %s\033[0m", i, cmd->args[i].str);
				else
					printf("ARG %d: %s\033[0m", i, cmd->args[i].str);
				if (cmd->args[i].interpret_env_var)
					printf("\033[1;32m INTERPRET\033[0m");
				if (cmd->args[i].quoted)
					printf(" quoted\n");
				printf("\n");
				printf("DEPTH: %d\n", cmd->depth);
				i++; 
			}
		}
		print_oper(cmd->operator_type);
		cmd = cmd->next;
	}
	printf("---------------end---------------\n");
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
	
	print_cmd(cmd);
	return (cmd);
}
