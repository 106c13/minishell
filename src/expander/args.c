/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:28:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/23 15:22:18 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_not_files_args(t_arg *args, int args_count)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < args_count)
	{
		if (args[i].file == 0)
			count += 1;
		i++;
	}
	return (count);
}

void	free_args(t_arg *arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i].str);
		i++;
	}
	free(arr);
}

t_arg	*append_arg(t_arg new, t_arg *old_arr, int *len)
{
	t_arg	*new_arr;
	int		i;

	new_arr = malloc(sizeof(t_arg) * (*len + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (old_arr && i < *len)
	{
		new_arr[i] = old_arr[i];
		i++;
	}
	new_arr[i] = new;
	*len = *len + 1;
	if (old_arr)
		free(old_arr);
	return (new_arr);
}

t_arg	new_arg_copy(char *str, t_arg *ref)
{
	t_arg	new;

	ft_memcpy(&new, ref, sizeof(t_arg));
	new.str = str;
	return (new);
}

t_arg	*split_and_append(char *str, t_arg *ref, t_arg *new_args, int *count)
{
	int		i;
	char	**split;
	t_arg	new;

	split = ft_split(str, ' ');
	i = 0;
	while (split && split[i])
	{
		if (split[i][0] != '\0')
		{
			new = new_arg_copy(ft_strdup(split[i]), ref);
			new_args = append_arg(new, new_args, count);
		}
		i++;
	}
	free_split(split);
	return (new_args);
}
