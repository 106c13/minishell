#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/* expand.c */
void	expand_command(t_ast	*leaf, t_shell *shell);
t_token	*expand_aliases(t_token *old, t_dict *aliases);

/* expand_utils.c */
char	*expand_speacial_character(char *arg, t_dict *env);
char	*add_chunk(char *dest, char **src, char *delim);
char	*expand_variable(char *dest, char **src, t_shell *shell);
char	*expand_quotes(char *dest, char **src, t_shell *shell);

#endif
