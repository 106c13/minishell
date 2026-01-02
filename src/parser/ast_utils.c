#include <stddef.h>
#include <stdlib.h>
#include "defines.h"
#include "minishell.h"
#include "tokenizer.h"
#include "utils.h"

static char	**create_argv(t_token *token)
{
	int		size;

	size = 0;
	while (t_is_redirect(token->type) || token->type == WORD)
	{
		if (token->type != WORD)
			token++;
		else
			size++;
		token++;
	}
	if (size == 0)
		return (NULL);
	return (malloc(sizeof(char *) * (size + 1)));
}

char	**extract_argv(t_token *token)
{
	char	**argv;
	int		i;

	argv = create_argv(token);
	if (!argv)
		return (NULL);
	i = 0;
	while (t_is_redirect(token->type) || token->type == WORD)
	{
		if (token->type != WORD)
			token++;
		else
			argv[i++] = ft_strdup(token->value);	
		token++;
	}
	argv[i] = NULL;
	return (argv);
}

static t_redir	*create_redirection(t_token *token)
{
	int	size;

	size = 0;
	while (t_is_redirect(token->type) || token->type == WORD)
	{
		if (t_is_redirect(token->type))
			size++;
		token++;
	}
	if (size == 0)
		return (NULL);
	return (malloc(sizeof(t_redir) * (size + 1)));
}

t_redir	*extract_redirections(t_token *token)
{
	int		i;
	t_redir	*redirs;

	redirs = create_redirection(token);
	if (!redirs)
		return (NULL);
	i = 0;
	while (t_is_redirect(token->type) || token->type == WORD)
	{
		if (t_is_redirect(token->type))
		{
			redirs[i].type = token->type; 
			token++;
			redirs[i++].file = ft_strdup(token->value);
		}
		token++;
	}
	redirs[i].type = 0;
	return (redirs);
}

void	clean_parentheses(t_token *left, t_token *right)
{
	t_token	*paren;

	left->type = UNUSED;
	while (right->type)
	{
		if (right->type == RPAREN)
			paren = right;
		right++;
	}
	paren->type = UNUSED;
}
