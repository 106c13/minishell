/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:11:44 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/18 20:12:32 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clear_quotes(char *str)
{
	char	*nstr;
	char	quote;
	int		size;
	int		i;

	if (!str)
		return (str);
	quote = 0;
	i = 0;
	nstr = malloc(sizeof(char) * (get_unquoted_len(str) + 1));
	if (!nstr)
		return (NULL);
	size = 0;
	while (str[size])
	{
		if (!quote && is_quote(str[size]))
			quote = str[size];
		else if (str[size] == quote)
			quote = 0;
		else
			nstr[i++] = str[size];
		size++;
	}
	nstr[i] = '\0';
	free(str);
	return (nstr);
}



int	setup_command(char *str, t_command *cmd)
{
	counter(str, cmd);
	cmd->args = malloc(sizeof(t_arg) * (cmd->args_count));
	if (!cmd->args)
		return (1);
	cmd->delimiters = malloc(sizeof(char *) * (cmd->delimiter_count + 1));
	if (!cmd->delimiters)
	{
		free(cmd->args);
		return (1);
	}
	cmd->delimiters[0] = NULL;
	cmd->cmd = cmd->args;
	return (0);
}
