/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:49:14 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/14 14:03:16 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_in_quotes(char *str)
{
	char	quote;
	int		size;

	size = 0;
	quote = *str;
	str++;
	while (str[size] && str[size] != quote)
		size++;
	return (size);
}

int	count_in_file(char *str)
{
	int	size;

	size = 0;
	while (!is_eow(str[size]))
	{
		if (str[size] == '\'' || str[size] == '"')
			size += count_in_quotes(str) + 2;
		else
			size++;
	}
	return (size);
}

void	skip_file(char **str, int *count)
{
	int	mode;

	mode = get_mode_type(*str);
	if (mode == APPEND || mode == HEREDOC)
		*str += 2;
	else
		*str += 1;
	*str = trim_spaces(*str);
	*str += count_in_file(*str);
	if (is_eow(**str) && mode != HEREDOC)
		(*count)++;
}

void	counter(char *str, t_command *cmd)
{
	while (*str && get_operator_type(str) == 0)
	{
		if (*str == '\'' || *str == '"')
		{
			str += count_in_quotes(str) + 2;
			if (is_eow(*(str)))
				cmd->args_count++;
		}
		else if (*str == '>')
			skip_file(&str, &cmd->out_file_count);
		else if (*str == '<')
			skip_file(&str, &cmd->in_file_count);
		else if (!is_whitespace(*str) && is_eow(*(str + 1)))
		{
			cmd->args_count++;
			str++;
		}
		else
			str++;
	}
//	printf("TESTING: ARG COUNT: %d %d %d\n", cmd->args_count, cmd->out_file_count, cmd->in_file_count);
}
