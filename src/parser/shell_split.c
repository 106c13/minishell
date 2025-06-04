/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:56:57 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/03 19:57:38 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	is_whitespace(char c)
{
	return (!c || c == ' ' || c == '\t');
}

static int	get_split_count(char *str)
{
	int		count;
	char	quote;

	count = 0;
	quote = 0;
	while (*str && get_operator_type(str) == 0)
	{
		if (!quote && (*str == '\'' || *str == '"'))
			quote = *str;
		else if (quote && *str == quote && is_whitespace(str[1]))
		{
			count++;
			quote = 0;
		}
		else if (!quote && !is_whitespace(*str) && is_whitespace(str[1]))
			count++;
		str++;
	}
	return (count);
}

int	get_arg_len(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (*str)
	{
		if (!quote && (*str == '"' || *str == '\''))
			quote = *str;
		else if (quote && *str == quote)
			quote = 0;
		else if (!quote && is_whitespace(*str))
			break ;
		else if (!quote && get_operator_type(str) != 0)
			break ;
		else
			i++;
		str++;
	}
	return (i);
}

void	add_arg(char **str, t_arg *arg, int size)
{
	char	quote;
	int		i;

	arg->arg = (char *)malloc(sizeof(char) * (size + 1));
	quote = 0;
	i = 0;
	arg->interpet_env_var = 0;
	arg->quoted = 0;
	if (!arg->arg)
		return ;
	arg->arg[size] = '\0';
	while (i < size)
	{
		if (!quote && (**str == '\'' || **str == '"'))
			quote = **str;
		else if (quote && **str == quote)
			quote = 0;
		else
		{
			if (quote == '"' && **str == '$')
			{
				arg->quoted = 1;
				arg->interpet_env_var = 1;
			}
			else if (!quote && **str == '$')
				arg->interpet_env_var = 1;
			arg->arg[i++] = **str;
		}
		(*str)++;
	}
	if (**str)
		(*str)++;
}

void	shell_split(char **str, t_command *cmd)
{
	int		split_count;
	t_arg	*args;
	int		arg_i;
	int		arg_len;

	split_count = get_split_count(*str);
	args = malloc(sizeof(t_arg) * (split_count));
	if (!args)
		return ;
	arg_i = 0;
	while (**str)
	{
		if (is_whitespace(**str))
			(*str)++;
		else if (get_operator_type(*str) != 0)
		{
			cmd->oper = get_operator_type(*str);
			if (cmd->oper < 3)
				*str += 2;
			else
				(*str)++;
			break ;
		}
		else
		{
			arg_len = get_arg_len(*str);
			add_arg(str, &args[arg_i], arg_len);
			arg_i++;
		}
	}
	cmd->args = args;
	cmd->args_count = split_count;
	cmd->cmd = &args[0];
}
