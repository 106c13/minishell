#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
#include "minishell.h"
#include "enviroment.h"

static t_list	*parse_env_line(char *env_line)
{
	char	*i;
	t_list	*new;

	i = ft_strchr(env_line, '=');
	if (!i)
		return (NULL);
	*i = '\0';
	new = new_env_node(env_line, i + 1);
	return (new);
}

char **env_to_array(t_list *env)
{
    char    **env_arr;
    char    *tmp;
    int     size;
    int     i;
    t_list   *curr;

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

t_list	*new_env_node(char *key, char *val)
{
	t_list	*new;

	new = ft_calloc(1, sizeof(t_list));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), NULL);
	if (val)
		new->val = ft_strdup(val);
	if (val && !new->val)
		return (free(new->key), free(new), NULL);
	return (new);
}

void	init_env_list(t_shell *shell, char **env_arr)
{
	t_list	*new;
	t_list	*prev;
	int		i;

	shell->env = NULL;
	i = -1;
	while (env_arr[++i])
	{
		new = parse_env_line(env_arr[i]);
		if (!new)
			continue ;
		if (shell->env == NULL)
			shell->env = new;
		else
			prev->next = new;
		prev = new;
	}
}
