#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>

typedef struct  s_token
{
    int             type;
    char            *value;
}   t_token;

typedef struct  s_redir
{
    int type;
    char    *file;
}   t_redir;

typedef struct  s_ast
{
    int              type;
    int             argc;
    char            **argv;
    t_redir         *redirs;
    struct s_ast    *left;
    struct s_ast    *right;
}   t_ast;

typedef struct s_list
{
	char			*key;
	char			*val;
	struct s_list    *next;
}	t_list;

typedef struct s_shell
{
    int     exec_result;
    pid_t   pid;
    t_list  *env;
    t_list  *aliases;
}   t_shell;

#endif
