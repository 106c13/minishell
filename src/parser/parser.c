/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:27 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/15 15:43:54 by haaghaja         ###   ########.fr       */
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
					printf(" quoted");
				printf("\n");
				i++; 
			}
		}
		print_oper(cmd->operator_type);
		cmd = cmd->next;
	}
	printf("---------------end---------------\n");
}
// ============================

t_command	*get_command(char	*input)
{
	t_command	*cmd;
	t_command	*tmp;
	t_command	*head;

	cmd = create_command();
	head = cmd;
	while (*input)
	{
		if (shell_split(&input, cmd) != 0)
			return (NULL);
		if (*input)
		{
			tmp = cmd;
			cmd = create_command();
			tmp->next = cmd;
		}
	}
	return (head);
}

t_command	*parse_command(char *input)
{
	t_command	*cmd;

	input = trim_spaces(input);
	if (!*input || validate(input) != 0)
		return (NULL);
	cmd = get_command(input);
	if (!cmd)
		return (NULL);
	
	print_cmd(cmd);
	return (cmd);
}
