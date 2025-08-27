#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "minishell.h"
#include "tokenizer.h"
#include "defines.h"
#include "parser.h"
#include "utils.h"


t_ast	*ast_subshell(t_token *token);

t_ast	*ast_leaf(t_token *token)
{
	t_ast	*leaf;

	printf("IN LEAF %d\n", token->type);
	leaf = ft_calloc(1, sizeof(t_ast));
	leaf->type = COMMAND;
	leaf->argv = extract_argv(token);
	leaf->argc = split_size(leaf->argv);
	leaf->redirs = extract_redirections(token);
	return (leaf);
}

t_token *find_higest_operator(t_token *token, bool *is_subshell)
{
	t_token	*op;
	int		depth;
	int		min_depth;

	min_depth = 1000;
	op = NULL;
	depth = 0;
	*is_subshell = false;
	while (token->type)
	{
		if (t_is_operator(token->type) && depth <= min_depth)
		{
			if (token->type == PIPE && !op)
				op = token;
			else if (token->type != PIPE)
				op = token;
			min_depth = depth;
			*is_subshell = (depth != 0);
		}
		else if (token->type == LPAREN)
			depth++;
		else if(token->type == RPAREN)
			depth--;
		token++;
	}
	return (op);
}

t_ast	*ast_subshell(t_token *token)
{
	t_ast	*node;

	printf("SUBSHELL-> ");
	node = malloc(sizeof(t_ast));
	node->type = SUBSHELL;
	node->left = NULL;
	node->right = build_ast(++token);
	return (node);
}


t_ast	*ast_node(t_token *left, t_token *right)
{
	t_ast	*node;

	printf("NODE-> ");
	node = malloc(sizeof(t_ast));
	node->type = right->type;
	right->type = 0;
	printf("LEFT-> ");
	node->left = build_ast(left);
	printf("RIGHT-> \n");
	node->right = build_ast(++right);
	return (node);
}

t_ast	*build_ast(t_token *token)
{
	t_token	*op;
	bool	is_subshell;

	if (!token)
		return (NULL);
	op = find_higest_operator(token, &is_subshell);
	if (is_subshell)
		clean_parentheses(token, op);
	if (is_subshell || (!op && token->type == LPAREN))
		return (ast_subshell(token));
	if (!op)
		return (ast_leaf(token));
	return (ast_node(token, op));
}
