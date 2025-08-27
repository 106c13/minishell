#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "utils.h"
#include "defines.h"


static t_list	*new_env_node(char *key, char *val)
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


static int	print_aliases(t_list *alias)
{
	while (alias)
	{
		printf("alias %s=%s", alias->key, alias->val);
		alias = alias->next;
	}
	return (SUCCESS);
}

static void	set_alias_val(t_list *env, char *key, char *val)
{
	t_list	*prev;

	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			if (!val || !*val)
				env->val = NULL;
			else
				env->val = ft_strdup(val);
			return ;
		}
		prev = env;
		env = env->next;
	}
	env = new_env_node(key, val);
	prev->next = env;
}

int	alias(t_ast *cmd, t_list *aliases)
{
	char	*key;
	char	*val;
	
	if (cmd->argc == 1)
		return (print_aliases(aliases));
	val = ft_strchr(cmd->argv[1], '=');
	if (val)
		*val++ = '\0';
	else
		return (FAILURE);
	key = cmd->argv[1];
	set_alias_val(aliases, key, val);
	return (SUCCESS);
}
