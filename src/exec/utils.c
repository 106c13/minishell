/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 17:01:48 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/15 17:02:32 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"

void set_exec_result(t_shell *shell, int status)
{
    if (WIFEXITED(status))
        shell->exec_result = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        shell->exec_result = 128 + WTERMSIG(status);
    else
        shell->exec_result = status;
}

