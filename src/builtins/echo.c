/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:25:16 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/27 18:14:52 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args, t_shell *shell)
{
	(void)args;
	(void)shell;
	char	n_flag;

	printf("echo mock\n");
	n_flag = 0;
	if (n_flag == 0)
		write(1, "\n", 1);
	return (1);
}
