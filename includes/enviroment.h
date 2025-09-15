#ifndef ENVIROMENT_H
# define ENVIROMENT_H

# include <stdbool.h>

/* env.c */
char	**env_to_array(t_dict *env);
void	init_env_list(t_shell *shell, char **env_arr);
bool	is_env_var(char *str);

#endif
