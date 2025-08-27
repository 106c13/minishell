#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdbool.h>
# include "minishell.h"

/* tokenizer.c */
t_token	*tokenize(char *input);

/* tokenizer_utils.c */
bool	check_token_array(t_token *token);
void	set_token_type(t_token *token, char *part);
int 	get_parts_size(char **parts);

/* token_utils.c */
void	set_token_type(t_token *token, char *part);
bool	t_is_parenthesis(int type);
bool	t_is_operator(int type);
bool	t_is_redirect(int type); 
#endif
