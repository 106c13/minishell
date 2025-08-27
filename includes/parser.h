#ifndef PARSER_H
# define PARSER_H
#   include "minishell.h"

/* ast.c */
t_ast	*build_ast(t_token *token);

/* ast_utils.c */
char	**extract_argv(t_token *token);
t_redir	*extract_redirections(t_token *token);
void	clean_parentheses(t_token *left, t_token *right);
#endif
