/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:41:25 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/26 18:47:09 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_shell_exit(t_shell *shell)
{
	printf("exit\n");
	rl_clear_history();
	free_env_list(shell);
	exit(0);
}
