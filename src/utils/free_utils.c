#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

void	free_argv(char **argv)
{
	int		i;

	if (!argv)
		return ;
	i = -1;
	while (argv[++i])
	{
		if (argv[i])
			free(argv[i]);
	}
	free(argv);
}

void	free_dict(t_dict *dict)
{
	t_dict	*tmp;

	while (dict)
	{
		tmp = dict;
		dict = dict->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
	}
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	if (!redir)
		return ;
	tmp = redir;
	while (redir->type != 0)
	{
		free(redir->file);
		redir++;
	}
	free(tmp);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
        return ;
	free_ast(ast->left);
    free_ast(ast->right);
    free_argv(ast->argv);
    free_redirs(ast->redirs);
    free(ast);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	tmp = token;
	while (token->type != 0)
	{
		if (token->value)
			free(token->value);
		token++;
	}
	free(tmp);
}
