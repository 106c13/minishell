#include <stdbool.h>
#include "defines.h"
#include "utils.h"

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	is_paren(char c)
{
	return (c == '(' || c == ')');
}

bool	is_redirect(char c)
{
	return (c == '>' || c == '<');
}

bool	is_operator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c =='\n');
}

bool	is_end(char c, char *delim)
{
	if (c == '\0')
		return (true);
	while (*delim)
	{
		if (c == *delim)
			return (true);
		delim++;
	}
	return (false);
}

int	get_operator_type(char *str)
{
	if (ft_strncmp(str, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(str, "&", 1) == 0)
		return (BG);
	if (ft_strncmp(str, "||", 2) == 0)
		return (OR);
	if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(str, ";", 1) == 0
		|| ft_strncmp(str, "\n", 1) == 0)
		return (SEMI);
	return (0);
}

int	get_parenthesis_type(char *str)
{
	if (*str == '(')
		return (LPAREN);
	if (*str == ')')
		return (RPAREN);
	return (0);
}

int	get_redirect_type(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (HEREDOC);
	if (ft_strncmp(str, ">", 1) == 0)
		return (OUTFILE);
	if (ft_strncmp(str, "<", 1) == 0)
		return (INFILE);
	return (0);
}
