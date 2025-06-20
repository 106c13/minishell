/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 14:11:11 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/20 14:33:19 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_delimiter(char **str, t_command *cmd)
{
	int	i;

	i = get_args_count(cmd->delimiters);
	cmd->delimiters[i] = ft_get_word(str);
	cmd->delimiters[i + 1] = NULL;
}

int	get_arg_len(char *str)
{
	int	size;

	size = 0;
	str = trim_spaces(str);
	while (!is_eow(str[size]))
	{
		if (is_quote(str[size]))
			size += count_in_quotes(&str[size]) + 2;
		else
			size++;
	}
	return (size);
}

int	get_mode_type(char	*mode)
{
	if (ft_strncmp(mode, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(mode, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(mode, ">", 1) == 0)
		return (TRUNCATE);
	if (ft_strncmp(mode, "<", 1) == 0)
		return (INPUT);
	return (0);
}
