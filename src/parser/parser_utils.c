/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:36:38 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/19 18:00:52 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_spaces(char *str)
{
	int	size;

	while (*str == ' ')
		str++;
	size = ft_strlen(str) - 1;
	while (str[size] == ' ')
		size--;
	str[size + 1] = '\0';
	return (str);
}

int	get_operator_type(char *word)
{
	if (ft_strncmp(word, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(word, "||", 2) == 0)
		return (OR);
	if (ft_strncmp(word, "&", 1) == 0)
		return (BG);
	if (ft_strncmp(word, "|", 1) == 0)
		return (PIPE);
	return (0);
}

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command) * 1);
	if (!cmd)
		return (NULL);
	ft_memset(cmd, 0, sizeof(t_command));
	cmd->argv = NULL;
	return (cmd);
}

int	get_unquoted_len(char	*str)
{
	char	quote;
	int		size;

	if (!str)
		return (0);
	size = 0;
	quote = 0;
	while (*str)
	{
		if (!quote && is_quote(*str))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else
			size++;
		str++;
	}
	return (size);
}
