/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:27 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/14 16:37:43 by azolotar         ###   ########.fr       */
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
				if (cmd->args[i].interpret_env_var)
					printf("\033[1;32m");
				else
					printf("\033[1;31m");
				printf("ARG %d: %s\033[0m", i, cmd->args[i].str);
				if (cmd->args[i].quoted)
					printf(" quoted\n");
				else
					printf("\n");
				i++; 
			}
		}
		if (cmd->output_files)
		{
			i = 0;
			while (i < cmd->out_file_count)
			{
				if (cmd->output_files[i].interpret_env_var)
					printf("\033[1;32m");
				else
					printf("\033[1;31m");
				printf("OUTPUT FILE %d: %s", i, cmd->output_files[i].name);
				if (cmd->output_files[i].mode == TRUNCATE)
					printf("\033[1;33m TURNCATE");
				else if (cmd->output_files[i].mode == APPEND)
					printf("\033[1;34m APPEND");
				else if (cmd->output_files[i].mode == INPUT)
					printf("\033[1;35m INPUT");
				printf("\033[0m\n");	
				i++; 
			}
			i = 0;
			while (i < cmd->in_file_count)
			{
				if (cmd->input_files[i].interpret_env_var)
					printf("\033[1;32m");
				else
					printf("\033[1;31m");
				printf("INPUT FILE %d: %s", i, cmd->input_files[i].name);
				if (cmd->input_files[i].mode == TRUNCATE)
					printf("\033[1;33m TURNCATE");
				else if (cmd->input_files[i].mode == APPEND)
					printf("\033[1;34m APPEND");
				else if (cmd->input_files[i].mode == INPUT)
					printf("\033[1;35m INPUT");
				printf("\033[0m\n");	
				i++; 
			}
		}
		if (cmd->delimiter)
			printf("HEREDOC: %s\n", cmd->delimiter);
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
