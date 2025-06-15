/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:28:30 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/15 19:40:46 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**args_to_argv(t_arg *args, int args_count)
{
	char	**argv;
	int		i;
	int		argc;
	int		j;

	if (!args || args_count == 0)
		return (NULL);
	argc = 0;
	i = 0;
	while (i < args_count)
	{
		if (args[i].file == 0)
			argc += 1;
		i++;
	}
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	j = 0;
	while (i < args_count)
	{
		if (args[i].file == 0)
		{
			argv[j] = ft_strdup(args[i].str);
			// handle bla bla bla
			j++;
		}
		i++;
	}
	argv[j] = NULL;
	return (argv);
}

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
