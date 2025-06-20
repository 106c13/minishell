/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:36:44 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/20 19:01:40 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_multiple_file(t_arg *args, int n)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < n)
	{
		if (args[i].file != 0 && args[i].wed == 1)
			count++;
		if (count > 1)
			return (1);
		i++;
	}
	return (0);
}
