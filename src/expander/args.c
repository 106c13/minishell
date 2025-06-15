/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:28:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/15 14:44:05 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_arg *arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
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
