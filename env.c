/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:56:08 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/22 23:21:42 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* DEBUG */
void	print_env_list(t_shell *shell)
{
	while (shell->env_list)
	{
		printf("key: %s, val: %s\n", shell->env_list->key, shell->env_list->val);
		shell->env_list = shell->env_list->next;
	}
}

static t_env	*new_env_node(char *key, char *val)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), NULL);
	new->val = ft_strdup(val);
	if (!new->val)
		return (free(new->key), free(new), NULL);
	new->next = NULL;
	return (new);
}

void	init_env_list(t_shell *shell, char **env_arr)
{
	char	**split;
	t_env	*new;
	t_env	*last;
	int		i;

	shell->env_list = NULL;
	last = NULL;
	i = -1;
	while (env_arr[++i])
	{
		split = ft_split(env_arr[i], '=');
		if (!split || !split[0] || !split[1])
		{
			if (split)
				free_split(split);
			continue ;
		}
		new = new_env_node(split[0], split[1]);
		free_split(split);
		if (!new)
		{
			free_env_list(shell);
			return ;
		}
		if (shell->env_list == NULL)
			shell->env_list = new;
		else
			last->next = new;
		last = new;
	}
	last->next = NULL;
}

void	free_env_list(t_shell *shell)
{
	t_env	*tmp;

	while (shell->env_list != NULL)
	{
		tmp = shell->env_list;
		shell->env_list = shell->env_list->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
	}
}
