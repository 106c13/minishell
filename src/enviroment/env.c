#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "minishell.h"
#include "enviroment.h"

char **env_to_array(t_dict *env)
{
    char    **env_arr;
    char    *tmp;
    int     size;
    int     i;
    t_dict   *curr;

    size = 0;
    curr = env;
    while (curr)
    {
        if (curr->val)
            size++;
        curr = curr->next;
    }
    env_arr = malloc(sizeof(char *) * (size + 1));
    if (!env_arr)
        return (NULL);
    i = 0;
    curr = env;
    while (curr)
    {
        if (curr->val)
        {
            tmp = ft_strjoin(curr->key, "=");
            if (!tmp)
                return (NULL); // handle allocation failure
            env_arr[i] = ft_strjoin(tmp, curr->val);
            free(tmp);
            if (!env_arr[i])
                return (NULL);
            i++;
        }
        curr = curr->next;
    }
    env_arr[i] = NULL;
    return (env_arr);
}

void	init_env_list(t_shell *shell, char **env_arr)
{
    char    *c;
	int		i;

	shell->env = NULL;
	i = -1;
	while (env_arr[++i])
	{
	    c = ft_strchr(env_arr[i], '=');
        if (!c)
            return ;
        *c = '\0';
		shell->env = set_dict_val(shell->env, env_arr[i], c + 1);
	}
}
