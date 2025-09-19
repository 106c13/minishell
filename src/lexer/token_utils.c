#include <stdbool.h>
#include "minishell.h"
#include "utils.h"
#include "defines.h"


bool	t_is_parenthesis(int	type)
{
	return (type == LPAREN || type == RPAREN);
}

bool	t_is_operator(int	type)
{
	return (type == AND 
			|| type == OR
			|| type == PIPE
			|| type == SEMI
			|| type == BG);
}

bool	t_is_redirect(int	type)
{
	return (type == OUTFILE
			|| type == INFILE
			|| type == APPEND
			|| type == HEREDOC);
}

void	set_token_type(t_token *token, char *part)
{
	if (is_paren(*part))
		token->type = get_parenthesis_type(part);
	else if (is_operator(*part))
		token->type = get_operator_type(part);
	else if (is_redirect(*part))
		token->type = get_redirect_type(part);
	else
		token->type = WORD;
}
