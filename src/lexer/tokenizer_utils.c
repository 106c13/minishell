#include <stdlib.h>
#include <stdbool.h>
#include "minishell.h"
#include "tokenizer.h"
#include "utils.h"
#include "defines.h"

/* checks if token is operator, parenthesis, or 0 */
static bool	is_valid_token(t_token *token)
{
	if (token->type == 0 || token->type == RPAREN)
		return (false);
	if (t_is_operator(token->type))
		return (false);
	return (true);
}

int	get_t_array_size(t_token *token)
{
	int	size;

	if (!token)
		return (0);
	size = 0;
	while(token->type)
	{
		size++;
		token++;
	}
	return (size);
}

bool	check_token_array(t_token *token)
{
	bool	is_first = true;
	int		depth = 0;

	while (token->type)
	{
		if ((is_first && !is_valid_token(token)) || (token->type == RPAREN && is_first) || (token->type == LPAREN && !is_first))
			return (syntax_error(token->type), false);
		if (token->type == RPAREN && depth == 0)
			return (syntax_error(token->type), false);
		if (token->type == LPAREN || t_is_operator(token->type))
			is_first = true;
		else
			is_first = false;
		if (token->type == LPAREN)
			depth++;
		else if (token->type == RPAREN)
			depth--;
		if ((t_is_operator(token->type) || t_is_redirect(token->type)) && token[1].type == 0)
			return (syntax_error(token->type), false);
		token++;
	}
	if (depth != 0)
		return (syntax_error(depth > 0 ? LPAREN : RPAREN), false);
	return true;
}
