/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:56:57 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/13 20:08:13 by haaghaja         ###   ########.fr       */
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

char	*ft_get_word(char **str)
{
	int	size;
	int	i;
	char	*word;

	size = get_arg_len(*str);
	i = 0;
	word = malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	while (i < size)
	{
		word[i++] = **str;
		(*str)++;
	}
	return (word);
}



void	add_file(char **str, t_file *file, t_command *cmd)
{
	int	size;
	int	mode;

	mode = get_mode_type(*str);
	if (mode == APPEND || mode == HEREDOC)
		*str += 2;
	else
		*str += 1;
	while (**str == ' ')
		(*str)++;
	if (mode == HEREDOC)
	{
		cmd->delimiter = ft_get_word(str);
		return ;
	}
	file->mode = mode;
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
			add_file(str, &cmd->output_files[out_i++], cmd);
		else if (**str == '<')
			add_file(str, &cmd->input_files[in_i++], cmd);
		else
			add_arg(str, &cmd->args[arg_i++]);	
	}
	return (0);
}
