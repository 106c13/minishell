/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:02:03 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/18 18:15:54 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate(char *input)
{
	int		op_type;
	int		is_cmd_start;
	int		is_file;
	int		file_len;
	char	quote;
	op_type = 0;
	quote = 0;
	is_file = 0;
	is_cmd_start = 0;
	while (*input)
	{
		if (is_whitespace(*input))
		{
			input++;
			continue ;
		}
		op_type = get_operator_type(input); 
		if (op_type != 0)
		{
			if (is_cmd_start || is_file)
				return (printerr_one("Invalid input"), 1);
			if (op_type == AND || op_type == OR)
				input++;
			input ++;
			continue ;
		}
		else if (*input == '>' || *input == '<')
		{
			input++;
			if (*input == '>')
				input++;
			is_file = 1;
			file_len = 0;
			input = trim_spaces(input);
			file_len = count_in_file(input);
			if (file_len == 0)
				return (printerr_one("syntax error near unexpected token `newline'"), 1);
		}
		if (is_quote(*input))
		{
			is_cmd_start = 1;
			input += count_in_quotes(input) + 2;
		}
		if (get_operator_type(input) && !is_cmd_start)
			return (printerr_one("Invalid input"), 1);
		else
			input++;
	}
	if (quote || op_type)
		return (printerr_one("Invalid input"), 1);
	return (0);
}
