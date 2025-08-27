#ifndef ENIVROMENT_H
# define ENVIROMENT_H

# include <stdbool.h>

/* env.c */
char	**env_to_array(t_list *env);
void	init_env_list(t_shell *shell, char **env_arr);
t_list	*new_env_node(char *key, char *val);

/* env_utils.c */
char	*get_env_val(t_list *env_list, char *key);
bool	is_env_var(char *str);
void	set_env_val(t_list *env, char *key, char *val);
void	free_env_list(t_shell *shell);
void	print_env(t_list *env);

#endif
