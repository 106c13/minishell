/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:45:06 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/30 18:14:52 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envlen(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

static int	get_env_sort_pos(char *env_key, t_env *env)
{
	int	pos;

	pos = 0;
	while (env)
	{
		if (ft_strcmp(env_key, env->key) > 0)
			pos++;
		env = env->next;
	}
	return (pos);
}

void	print_export_env(t_env *env)
{
	int		env_len;
	int		printed_count;
	int		pos;
	t_env	*tmp;

	env_len = envlen(env);
	printed_count = 0;
	while (printed_count != env_len)
	{
		tmp = env;
		while (tmp)
		{
			pos = get_env_sort_pos(tmp->key, env);
			if (pos == printed_count)
			{
				if (ft_strcmp(tmp->key, "_") != 0)
				{
					if (tmp->val == NULL)
						printf("%s=''\n", tmp->key);
					else
						printf("%s=%s\n", tmp->key, tmp->val);
				}
				printed_count += 1;
			}
			tmp = tmp->next;
		}
	}
}

int	env_contains(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

char	**env_list_to_str_arr(t_env *env)
{
	char	**result;
	char	*tmp;
	int		i;

	result = malloc(sizeof(char *) * (envlen(env) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (env)
	{
		result[i] = ft_strjoin(env->key, "=");
		tmp = result[i];
		result[i] = ft_strjoin(result[i], env->val);
		free(tmp);
		i++;
		env = env->next;
	}
	result[i] = NULL;
	return (result);
}
