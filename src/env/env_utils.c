/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:45:06 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/29 19:51:44 by azolotar         ###   ########.fr       */
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
