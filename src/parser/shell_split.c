/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:56:57 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/18 22:43:50 by haaghaja         ###   ########.fr       */
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

int	is_env(char *str)
{
	if (*str == '$')
	{
		if (str[1] == '?')
			return (1);
		else if (ft_isalnum(str[1]) || str[1] == '_')
			return (1);
	}
	return (0);
}

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
	word[size] = '\0';
	return (word);
}

void	add_delimiter(char **str, t_command *cmd)
{
	int	i;

	i = get_args_count(cmd->delimiters);
	cmd->delimiters[i] = ft_get_word(str);
	cmd->delimiters[i + 1] = NULL;
}

void	add_arg(char **str, t_command *cmd, int *arg_i)
{
	int	size;
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
	cmd->args[*arg_i].append = 0;
	cmd->args[*arg_i].file = 0;
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




int	shell_split(char **str, t_command *cmd)
{
	int		arg_i;
	int		global_depth;

	if (setup_command(*str, cmd) != 0)
		return (1);
	arg_i = 0;
	global_depth = cmd->depth;
	while (**str)
	{
		if (is_whitespace(**str))
			(*str)++;
		else if (get_operator_type(*str) != 0)
		{
			set_operator(str, cmd, global_depth);
			break ;
		}
		else if (**str == ')')
		{
			global_depth--;
			cmd->last_in_group = 1;
			(*str)++;
		}
		else if (**str == '(')
		{
			global_depth++;
			cmd->depth++;
			(*str)++;
		}
		else if (**str == '>' || **str == '<')
			add_arg(str, cmd, &arg_i);	
		else
			add_arg(str, cmd, &arg_i);	
	}
	return (0);
}
