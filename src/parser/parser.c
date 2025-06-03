/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:27 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/03 20:11:57 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// ONLY for tests
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
				printf("ARG %d: %s  expand: %d\n", i, cmd->args[i].arg, cmd->args[i].interpet_env_var);
				i++;  
			}
		}
		printf("OPERATOR: %d\n", cmd->oper);
		cmd = cmd->next;
	}
	printf("---------------end---------------\n");
}

t_command	*get_command(char	*input)
{
	t_command	*cmd;
	t_command	*tmp;
	t_command	*head;

	cmd = create_command();
	head = cmd;
	while (*input)
	{
		shell_split(&input, cmd);
		print_cmd(cmd);
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
	char		**words;

	input = trim_spaces(input);
	if (*input == '\0')
		return (NULL);
	cmd = get_command(input);
	if (!cmd)
		return (NULL);
	//print_cmd(cmd);
	return (cmd);
}
