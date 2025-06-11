/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:27 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/10 20:14:58 by azolotar         ###   ########.fr       */
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
		printf("COMMAND: %s\n", cmd->cmd->arg);
		i = 0;
		if (cmd->args)
		{
			while (i < cmd->args_count)
			{
				if (cmd->args[i].interpet_env_var)
					printf("\033[1;32m");
				else
					printf("\033[1;31m");
				printf("ARG %d: %s\033[0m\n", i, cmd->args[i].arg);
				i++; 
			}
		}
		if (cmd->output_files)
		{
			i = 0;
			while (i < cmd->files_count)
			{
				if (cmd->output_files[i].interpet_env_var)
					printf("\033[1;32m");
				else
					printf("\033[1;31m");
				printf("FILE %d: %s\033[0m\n", i, cmd->output_files[i].arg);
				i++; 
			}
		}
		print_oper(cmd->oper);
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
	
//	print_cmd(cmd);
	return (cmd);
}
