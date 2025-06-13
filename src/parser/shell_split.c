/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:56:57 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/13 19:03:13 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg_len(char *str)
{
	int	size;

	size = 0;
	str = trim_spaces(str);
	while(!is_eow(str[size]))
	{
		if (is_quote(str[size]))
			size += count_in_quotes(&str[size]) + 2;
		else
			size++;
	}
	return (size);
}

void	add_word(char **str, t_arg *arg, int size)
{
	char	quote;
	int		i;
	

	arg->arg = (char *)malloc(sizeof(char) * (size + 1));
	quote = 0;
	i = 0;
	arg->interpet_env_var = 0;
	if (!arg->arg)
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
		if ((!quote || quote == '"') && **str == '$')
			arg->interpet_env_var = 1;
		arg->arg[i++] = **str;
		(*str)++;
	}
	arg->arg[size] = '\0';
}

//==================TEMPRORARY======================

void	add_word_f(char **str, t_file *file, int size)
{
	char	quote;
	int		i;
	

	file->name = (char *)malloc(sizeof(char) * (size + 1));
	quote = 0;
	i = 0;
	file->interpet_env_var = 0;
	if (!file->name)
		return ;
	while (i < size)
	{
		if (!quote && is_quote(**str))
			quote = **str;
		else if (quote && **str == quote)
		{
			quote = 0;
			if (i != size - 1)
				file->quoted = 0;
		}
		if ((!quote || quote == '"') && **str == '$')
			file->interpet_env_var = 1;
		file->name[i++] = **str;
		(*str)++;
	}
	file->name[size] = '\0';
}
//==================================================



int	setup_command(char *str, t_command *cmd)
{
	counter(str, cmd);
	cmd->args = malloc(sizeof(t_arg) * (cmd->args_count));
	if (!cmd->args)
		return (1);
	cmd->output_files = malloc(sizeof(t_arg) * (cmd->out_file_count));
	if (!cmd->output_files)
	{
		free(cmd->args);
		return (1);
	}
	cmd->input_files = malloc(sizeof(t_arg) * (cmd->in_file_count));
	if (!cmd->input_files)
	{
		free(cmd->args);
		free(cmd->output_files);
		return (1);
	}
	cmd->cmd = cmd->args;
	return (0);
}

void	add_file(char **str, t_file *file)
{
	int	size;
	char	c;

	c = **str;
	if (**str == c)
		(*str)++;
	if (**str == c)
		(*str)++;
	while (**str == ' ')
		(*str)++;
	size = get_arg_len(*str);
	add_word_f(str, file, size);
}

void	add_arg(char **str, t_arg *arg)
{
	int	size;

	if (is_quote(**str))
		arg->quoted = 2;
	else
		arg->quoted = 0;
	size = get_arg_len(*str);
	add_word(str, arg, size);
	if (is_quote(**str) && arg->quoted == 2)
		arg->quoted = 1;
}

int	shell_split(char **str, t_command *cmd)
{
	int		arg_i;
	int		out_i;
	int		in_i;

	if (setup_command(*str, cmd) != 0)
		return (1);
	arg_i = 0;
	out_i = 0;
	in_i = 0;
	while (**str)
	{
		if (is_whitespace(**str))
			(*str)++;
		else if (get_operator_type(*str) != 0)
		{
			set_operator(str, cmd);
			break ;
		}
		else if (**str == '>')
			add_file(str, &cmd->output_files[out_i++]);
		else if (**str == '<')
			add_file(str, &cmd->input_files[in_i++]);
		else
			add_arg(str, &cmd->args[arg_i++]);	
	}
	return (0);
}
