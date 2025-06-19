/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:46:42 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/19 20:22:17 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shlvl(t_env *env)
{
	char	*old_str_val;
	int		int_val;
	char	*new_str_val;

	old_str_val = get_env_val(env, "SHLVL");
	if (!old_str_val)
	{
		set_env_val(env, "SHLVL", "0");
		return ;
	}
	int_val = ft_atoi(old_str_val);
	if (int_val < 0)
		int_val = 0;
	int_val += 1;
	new_str_val = ft_itoa(int_val);
	if (!new_str_val)
		return ;
	set_env_val(env, "SHLVL", new_str_val);
	free(new_str_val);
}
