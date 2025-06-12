#include "minishell.h"

int	count_in_quotes(char **str)
{
	char	quote;
	int	size;

	size = 0;
	quote = **str;
	(*str)++;
	while (**str && **str != quote)
	{
		size++;
		(*str)++;
	}
	(*str)++;
	return (size);
}

int	is_eow(char c)
{
	if (is_whitespace(c))
		return (1);
	if (c == '>' || c == '<' || c == '&' || c == '|')
		return (1);
	return (0);
}

int	count_in_file(char **str)
{
	*str = trim_spaces(*str);
	while (**str && !is_eow(**str))
	{
		if (**str == '\'' || **str == '"')
			count_in_quotes(str);
		else
			(*str)++;
	}
	return (1);
}


void	counter(char *str, t_command *cmd)
{
	while (*str && get_operator_type(str) == 0)
	{
		if (*str == '\'' || *str == '"')
		{
			count_in_quotes(&str);
			if (is_eow(*(str)))
				cmd->args_count++;
		}
		else if (*str == '>')
		{
			if (*str == '>')
				str++;
			if (*str == '>')
				str++;
			count_in_file(&str);
			if (is_eow(*(str)))
				cmd->out_file_count++;
		}
		else if (*str == '<')
		{
			if (*str == '<')
				str++;
			count_in_file(&str);
			if (is_eow(*(str)))
				cmd->in_file_count++;
		}
		else if (!is_whitespace(*str) && is_eow(*(str + 1)))
		{
			cmd->args_count++;
			str++;
		}
		else
			str++;
	}
	//printf("TESTING: ARG COUNT: %d %d %d\n", cmd->args_count, cmd->out_file_count, cmd->in_file_count);
}
