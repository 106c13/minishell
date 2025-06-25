/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:27 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/25 15:57:47 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (cmd);
}
