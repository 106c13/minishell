#include <stdio.h>
#include "minishell.h"
#include "enviroment.h"
#include "utils.h"


void	set_env_val(t_list *env, char *key, char *val)
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

char	*get_env_val(t_list *env, char *key)
{
	if (!env || !key)
		return (NULL);
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

void	free_env_list(t_shell *shell)
{
	t_list	*tmp;

	while (shell->env != NULL)
	{
		tmp = shell->env;
		shell->env = shell->env->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
	}
}

bool	is_env_var(char *str)
{
	return (*str == '$' && (ft_isalnum(str[1]) || str[1] == '_' || str[1] == '?'));
}

void	print_env(t_list *env)
{
	while (env)
	{
		if (env->val == NULL)
			printf("%s\n", env->key);
		else
			printf("%s=\"%s\"\n", env->key, env->val);
		env = env->next;
	}
}
