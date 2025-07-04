/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:56:57 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/23 15:24:45 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_word(char **str, t_arg *arg, int size)
{
	char	quote;
	int		i;

	arg->str = (char *)malloc(sizeof(char) * (size + 1));
	quote = 0;
	i = 0;
	arg->interpret_env_var = 0;
	if (!arg->str)
		return ;
	while (i < size)
	{
		if (!quote && is_quote(**str))
			quote = **str;
		else if (quote && **str == quote)
		{
			quote = 0;
			if (i != size - 1)
				arg->quoted = 0;
		}
		if ((!quote || quote == '"') && is_env(*str))
			arg->interpret_env_var = 1;
		arg->str[i++] = **str;
		(*str)++;
	}
	arg->str[size] = '\0';
}

void	add_arg2(char **str, t_command *cmd, int *arg_i, int mode)
{
	int	size;

	if (is_quote(**str))
		cmd->args[*arg_i].quoted = 2;
	else
		cmd->args[*arg_i].quoted = 0;
	if (mode == APPEND)
		cmd->args[*arg_i].append = 1;
	if (mode == APPEND || mode == TRUNCATE)
		cmd->args[*arg_i].file = 2;
	if (mode == INPUT)
		cmd->args[*arg_i].file = 1;
	size = get_arg_len(*str);
	add_word(str, &cmd->args[*arg_i], size);
	if (is_quote(**str) && cmd->args[*arg_i].quoted == 2)
		cmd->args[*arg_i].quoted = 1;
	(*arg_i)++;
}

void	add_arg(char **str, char *tmp, t_command *cmd, int *arg_i)
{
	int	mode;

	mode = get_mode_type(*str);
	if (mode == APPEND || mode == HEREDOC)
		*str += 2;
	else if (mode == TRUNCATE || mode == INPUT)
		*str += 1;
	while (**str == ' ')
		(*str)++;
	if (mode == HEREDOC)
	{
		add_delimiter(str, cmd);
		return ;
	}
	cmd->args[*arg_i].depth = calculate_depth(tmp, *str);
	cmd->args[*arg_i].append = 0;
	cmd->args[*arg_i].file = 0;
	cmd->args[*arg_i].wed = 0;
	add_arg2(str, cmd, arg_i, mode);
}

int	shell_split(char **str, char *start, t_command *cmd)
{
	int		arg_i;

	if (setup_command(*str, cmd) != 0)
		return (1);
	arg_i = 0;
	while (**str)
	{
		if (is_whitespace(**str))
			(*str)++;
		else if (get_operator_type(*str) != 0)
			return (set_operator(str, cmd, start));
		else if (**str == ')')
		{
			cmd->last_in_group = 1;
			(*str)++;
		}
		else if (**str == '(')
		{
			cmd->depth++;
			(*str)++;
		}
		else
			add_arg(str, start, cmd, &arg_i);
	}
	return (0);
}
