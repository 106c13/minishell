/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:58:34 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/16 16:48:06 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "defines.h"
#include "utils.h"

int	print_env_list(t_ast *cmd, t_dict *env)
{
	if (cmd->argc != 1)
	{
		printf("minishell: env: too many arguments\n");
		return (FAILURE);
	}
	print_dict(env);
	return (SUCCESS);
}
