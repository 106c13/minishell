#include "minishell.h"

int	count_in_quotes(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str && **str != quote)
		(*str)++;
	return (1);
}

int	is_eow(char c)
{
	if (is_whitespace(c))
		return (1);
	if (c == '>' || c == '&' || c == '|')
		return (1);
	return (0);
}

int	count_in_file(char **str)
{
	int	in_file;

	if (**str == '>')
		(*str)++;
	if (**str == '>')
		(*str)++;
	in_file = 0;
	while (**str)
	{
		if (!is_whitespace(**str))
			in_file = 1;
		if (**str == '\'' || **str == '"')
			count_in_quotes(str);
		else if (in_file && is_eow(*(*str + 1)))
			break ;
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
			if (is_eow(*(str + 1)))
				cmd->args_count++;
		}
		else if (*str == '>')
		{
			count_in_file(&str);
			if (is_eow(*(str + 1)))
				cmd->files_count++;
		}
		else if (!is_whitespace(*str) && is_eow(*(str + 1)))
			cmd->args_count++;
		if (*str)
			str++;
	}
	printf("TESTING: ARG COUNT: %d %d\n", cmd->args_count, cmd->files_count);
}
