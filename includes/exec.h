#ifndef EXEC_H
# define EXEC_H

# include <stdbool.h>

/* exec.c */
int		execute_node(t_ast *node, t_shell *shell);

/* exec_utils.c */
void	execute_pipe_node(t_ast *node, t_shell *shell, int *pipefd);
char	*find_executable(char *cmd, t_dict *env);
int 	is_builtin(char *cmd);
int		execute_subshell(t_ast *node, t_shell *shell);

/* redirection_utils.c */
bool    redirect_out(char *file);
bool	restore_fds(int	*fds);
bool	setup_redirections(int *fds, t_redir *redirs);


/* cd.c */ 
int		change_dir(t_ast *leaf, t_dict *env);

/* echo.c */
int		echo(t_ast  *leaf);

/* exit.c */
int	shell_exit(t_ast *leaf, t_shell *shell);

/* pwd.c */
int		print_working_dir(t_ast *leaf);

/* export */
int		export_env(t_ast *cmd, t_dict *env);

/* env */
int		print_env_list(t_ast *cmd, t_dict *env);

/* alias */
int		alias(t_ast *cmd, t_dict **aliases);
#endif
