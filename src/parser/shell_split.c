/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:56:57 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/05 18:23:41 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	is_whitespace(char c)
{
	return (!c || c == ' ' || c == '\t');
}

int	get_fname_size(char **str)
{
	char	quote;
	int	size;
	int	is_fname;

	quote = 0;
	size = 0;
	is_fname = 0;
	if (**str == '>')
		(*str)++;
	if (**str == '>')
		(*str)++;
	while(**str)
	{
		if (!quote && (**str == '\'' || **str == '"'))
		{
			quote = **str;
			is_fname = 1;
		}
		else if (**str == quote)
			quote = 0;
		if (!quote)
		{
			if (**str == '>')
				break ;
			else if (!is_whitespace(**str))
			{
				is_fname = 1;
				size++;
			}
			else if (is_fname)
				break ;
		}
		else if (is_fname)
			size++;
		(*str)++;
	}
	//printf("File size: %d\n", size);
	return (size);
}

static void	get_split_count(char *str, t_command *cmd)
{
	char	quote;

	quote = 0;
	while (*str)
	{
		//printf("%s %d\n", str, quote);
		if (!quote && (*str == '\'' || *str == '"'))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		if (!quote)
		{
			if (*str == '>')
			{
				get_fname_size(&str);
				cmd->files_count++;
				continue ;
			}
			else if (!is_whitespace(*str) && is_whitespace(str[1]))
				cmd->args_count++;
			else if (!is_whitespace(*str) && get_operator_type(str + 1) != 0)
			{
				cmd->args_count++;
				break ;
			}
			else if (is_whitespace(*str) && get_operator_type(str + 1) != 0)
				break ;
		}
		str++;
	}
	//printf("TESTING: ARG COUNT: %d %d\n", cmd->args_count, cmd->files_count);
}

int	get_arg_len(char *str)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	//printf("%s\n", str);
	while (*str)
	{
		if (!quote && (*str == '"' || *str == '\''))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		if (!quote && is_whitespace(*str))
			break ;
		else if (!quote && get_operator_type(str) != 0)
			break ;
		else if (!quote && *str == '>')
			break ;
		else
			i++;
		str++;
	}
	//printf("TESTING: ARG LEN: %d\n", i);
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
		
		if (quote == '"' && **str == '$')
		{
			arg->quoted = 1;
			arg->interpet_env_var = 1;
		}
		else if (!quote && **str == '$')
			arg->interpet_env_var = 1;
		arg->arg[i++] = **str;
		(*str)++;
	}
	//printf("STOPED: %s\n", *str);
}

void	shell_split(char **str, t_command *cmd)
{
	t_arg	*args;
	t_arg	*output_files;
	char	*tmp;
	int		arg_i;
	int		file_i;
	int		arg_len;

	get_split_count(*str, cmd);
	args = malloc(sizeof(t_arg) * (cmd->args_count));
	output_files = malloc(sizeof(t_arg) * (cmd->files_count));
	if (!args || !output_files)
		return ;
	arg_i = 0;
	file_i = 0;
	while (**str)
	{
		if (is_whitespace(**str))
			(*str)++;
		else if (get_operator_type(*str) != 0)
		{
			cmd->oper = get_operator_type(*str);
			if (cmd->oper == OR || cmd->oper == AND)
				*str += 2;
			else
				(*str)++;
			break ;
		}
		else if (**str == '>')
		{
			if (**str == '>')
				(*str)++;
			if (**str == '>')
				(*str)++;
			while (**str == ' ')
				(*str)++;
			tmp = *str;
			arg_len = get_fname_size(&tmp);
			add_arg(str, &output_files[file_i], arg_len);
			file_i++;
		}
		else
		{
			arg_len = get_arg_len(*str);
			add_arg(str, &args[arg_i], arg_len);
			arg_i++;
		}
	}
	cmd->args = args;
	cmd->output_files = output_files;
	cmd->cmd = &args[0];
}
