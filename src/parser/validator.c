#include "minishell.h"

static int	ft_error(char *msg)
{
	printf("%s\n", msg);
	return (1);
}

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int	is_starts_with_operator(char *input)
{
	if (get_operator_type(input) != 0)
		return (1);
	return (0);
}

int	validate(char *input)
{
	int		op_type;
	char	quote;

	op_type = 0;
	quote = 0;
	if (is_starts_with_operator(input))
		return (ft_error("Invalid input"));
	while (*input)
	{
		if (!quote)
		{
			if (is_quote(*input))
				quote = *input;
			if (!op_type && get_operator_type(input) != 0)
				op_type = get_operator_type(input);
			else if (op_type != 0 && get_operator_type(input) == 0)
				op_type = 0;
		}
		else if (quote == *input)
			quote = 0;
		input++;
	}
	if (quote || op_type)
		return (ft_error("Invalid input"));
	return (0);
}
