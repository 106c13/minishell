#ifndef UTILS_H
# define UTILS_H

#include <stdbool.h>
#include <stdlib.h>
#include "minishell.h"

/* string_utils.c */
bool	is_whitespace(char c);
bool    is_quote(char c);
bool	is_paren(char c);
bool	is_operator(char c);
bool    is_redirect(char c);
bool    is_end(char c, char *delim);
int     get_operator_type(char *str);
int 	get_redirect_type(char *str);
int 	get_parenthesis_type(char *str);

/* error_utils.c */
void	syntax_error(int type);

/* utils.c */
int	get_redirs_size(t_redir *redirs);

/* skip_utils.c */
int 	skip_operator(char **str);
int	    skip_redirect(char **str);
int 	skip_quote(char **str);
int	    skip_spaces(char **str);
int	    skip_part(char **str);

/* split.c */
char	**split_command(char *input);

/* split_utils.c */
int		split_size(char **parts);
int	    count_parts(char *line);
char	*get_part(char **str);
void    free_parts(char **parts, int size);

/* free_utils.c */
void	free_argv(int argc, char **argv);

/* Basic functions */
int	    ft_strcmp(const char *s1, const char *s2);
int	    ft_strncmp(const char *s1, const char *s2, int n);
char	*ft_strdup(const char *src);
char	*ft_strchr(const char *s, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_bzero(void *s, size_t n);
char	*ft_strnjoin(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_isalnum(char c);
char	*ft_itoa(int num);
int		ft_isalpha(int c);
#endif
