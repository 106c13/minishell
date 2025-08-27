#include "defines.h"
#include "utils.h"

int	skip_operator(char **str)
{
	int	type;

	type = get_operator_type(*str);
	if (type == AND || type == OR)
	{
		(*str) += 2;
		return (2);
	}
	(*str)++;
	return (1);
}

int	skip_spaces(char **str)
{
	int	size;

	size = 0;
	while (is_whitespace(**str))
	{
		(*str)++;
		size++;
	}
	return (size);
}

int	skip_quote(char **str)
{
	int		size;
	char	quote;

	size = 2;
	quote = **str;
	(*str)++;
	while (**str && **str != quote)
	{
		(*str)++;
		size++;
	}
	if (!**str)
		return (-1);
	(*str)++;
	return (size);
}

int	skip_redirect(char **str)
{
	int	type;

	type = get_redirect_type(*str);
	(*str)++;
	if (type == HEREDOC || type == APPEND)
	{
		(*str)++;
		return (2);
	}
	return (1);
}

int	skip_part(char **str)
{
	int	size;

	size = 0;
	if (is_operator(**str))
		return (skip_operator(str));
	if (is_redirect(**str))
		return (skip_redirect(str));
	if (is_paren(**str))
	{
		(*str)++;
		return (1);
	}
	while (!is_end(**str, "()>< &|;"))
	{
		if (is_quote(**str))
			size += skip_quote(str);
		else
		{
			(*str)++;
			size++;
		}
	}
	return (size);
}
