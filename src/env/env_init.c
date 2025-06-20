/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:56:08 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 15:04:05 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_node(char *key, char *val)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), NULL);
	if (val == NULL)
		new->val = NULL;
	else
	{
		new->val = ft_strdup(val);
		if (!new->val)
			return (free(new->key), free(new), NULL);
	}
	new->next = NULL;
	return (new);
}

static t_env	*parse_env_line(char *env_line)
{
	char	*equal_sign_loc;
	char	*key;
	char	*val;
	t_env	*new;

	equal_sign_loc = ft_strchr(env_line, '=');
	if (!equal_sign_loc)
		return (NULL);
	key = ft_substr(env_line, 0, equal_sign_loc - env_line);
	if (!key)
		return (NULL);
	val = ft_strdup(equal_sign_loc + 1);
	if (!val)
		return (free(key), NULL);
	new = new_env_node(key, val);
	free(key);
	free(val);
	return (new);
}

void	init_env_list(t_shell *shell, char **env_arr)
{
	t_env	*new;
	t_env	*last;
	int		i;

	shell->env_list = NULL;
	shell->job_list = NULL;
	last = NULL;
	i = -1;
	while (env_arr[++i])
	{
		new = parse_env_line(env_arr[i]);
		if (!new)
			continue ;
		if (shell->env_list == NULL)
			shell->env_list = new;
		else
			last->next = new;
		last = new;
	}
	if (last)
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
