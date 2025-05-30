/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:27 by haaghaja          #+#    #+#             */
/*   Updated: 2025/05/30 18:12:36 by haaghaja         ###   ########.fr       */
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
		printf("COMMAND: %s\n", cmd->cmd);
		i = 0;
		if (cmd->args)
		{
			while (cmd->args[i])
			{
				printf("ARG %d: %s\n", i, cmd->args[i]);
				i++;  
			}
		}
		printf("OPERATOR: %d\n", cmd->oper);
		cmd = cmd->next;
	}
	printf("---------------end---------------\n");
}

int	parse_word(char	**words, t_command *cmd)
{
	int	i;
	int	op_type;
	t_command *tmp;

	i = 0;
	while (words[i])
	{
		if (cmd->cmd == NULL)
			cmd->cmd = ft_strcpy(words[i]);
		if (cmd->args == NULL)
			cmd->args = &words[i];
		op_type = get_operator_type(words[i]);
		if (op_type != 0)
		{
			free(words[i]);
			words[i] = NULL;
			tmp = cmd;
			// TODO: Check malloc
			cmd = malloc(sizeof(t_command) * 1);
			cmd->cmd = NULL;
			cmd->args = NULL;
			cmd->next = NULL;
			cmd->oper = 0;
			tmp->next = cmd;
			tmp->oper = op_type;
		}
		i++;
	}
	return (0);
}



t_command	*parse_command(char *input)
{
	t_command	*cmd;
	char		**words;

	input = trim_spaces(input);
	if (*input == '\0')
		return (NULL);
	words = ft_split(input, ' ');
	// add malloc check
	cmd = malloc(sizeof(t_command) * 1);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->oper = 0;
	if (!cmd)
		return (NULL);
	if (parse_word(words, cmd) != 0)
		return (NULL);
	//print_cmd(cmd);
	return (cmd);
}


