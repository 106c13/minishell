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

int	is_whitespace(char c)
{
	return (!c || c == ' ' || c == '\t');
}

int	get_fname_size(char *str)
{
	char	quote;
	int	size;

	quote = 0;
	size = 0;
	if (*str == '>')
		str++;
	if (*str == '>')
		str++;
	str = trim_spaces(str);
	while(*str)
	{
		if (!quote && (*str == '\'' || *str == '"'))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		size++;
		if (!quote && is_eow(*(str + 1)))
			break ;
		str++;
	}
	//printf("File size: %d\n", size);
	return (size);
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
	if (!arg->arg)
		return ;
	arg->arg[size] = '\0';
	while (i < size)
	{
		if (!quote && (**str == '\'' || **str == '"'))
			quote = **str;
		else if (quote && **str == quote)
		{
			quote = 0;
			if (i != size - 1)
				arg->quoted = 0;
		}
		if (quote == '"' && **str == '$')
			arg->interpet_env_var = 1;
		else if (!quote && **str == '$')
			arg->interpet_env_var = 1;
		arg->arg[i++] = **str;
		(*str)++;
	}
	//printf("STOPED: %s\n", *str);
}

int	setup_command(char *str, t_command *cmd)
{
	counter(str, cmd);
	cmd->args = malloc(sizeof(t_arg) * (cmd->args_count));
	if (!cmd->args)
		return (1);
	cmd->output_files = malloc(sizeof(t_arg) * (cmd->files_count));
	if (!cmd->output_files)
	{
		free(cmd->args);
		return (1);
	}
	cmd->cmd = cmd->args;
	return (0);
}

void	set_operator(char **str, t_command *cmd)
{
	cmd->oper = get_operator_type(*str);
	if (cmd->oper == OR || cmd->oper == AND)
		*str += 2;
	else
		(*str)++;
}

void	add_file(char **str, t_arg *file)
{
	int	size;

	if (**str == '>')
		(*str)++;
	if (**str == '>')
		(*str)++;
	while (**str == ' ')
		(*str)++;
	size = get_fname_size(*str);
	add_arg(str, file, size);
}


int	shell_split(char **str, t_command *cmd)
{
	int		arg_i;
	int		file_i;
	int		arg_len;

	if (setup_command(*str, cmd) != 0)
		return (1);
	arg_i = 0;
	file_i = 0;
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
			add_file(str, &cmd->output_files[file_i++]);
		else
		{
			printf("|%s|\n", *str);
			if (**str == '"')
				cmd->args[arg_i].quoted = 2;
			arg_len = get_arg_len(*str);
			add_arg(str, &cmd->args[arg_i], arg_len);
			printf("%d\n", cmd->args[arg_i].quoted);
			printf("|%s|\n", *str - 1);
			if (*(*str - 1) == '"' && cmd->args[arg_i].quoted == 2)
				cmd->args[arg_i].quoted = 1;
			arg_i++;
		}
	}
	return (0);
}
