/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:41:25 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/17 20:21:29 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"

static int	is_valid_number(char *str)
{
	int	i;

	if (ft_strlen(str) > 20)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i += 1;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_strtoll_overflow(const char *str, long long *out)
{
	long long	result;
	int			sign;
	int			i;
	int			digit;

	result = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		digit = str[i] - '0';
		if (sign == 1)
		{
			if (result > (LLONG_MAX - digit) / 10)
				return (1);
		}
		else
		{
			if (-result < (LLONG_MIN + digit) / 10)
				return (1);
		}
		result = result * 10 + digit;
		i++;
	}
	*out = sign * result;
	return (0);
}

int safe_shell_exit(t_command *cmd, t_shell *shell)
{
	long long	exit_code;
	char		*arg;

	exit_code = SUCCESS;
	printf("exit\n");
	if (cmd != NULL && cmd->argc > 2)
	{
		printerr_two("exit", "too many arguments");
		return (FAILURE);
	}
	if (cmd != NULL && cmd->argc == 2)
	{
		arg = cmd->argv[1];
		if (is_valid_number(arg) && !ft_strtoll_overflow(arg, &exit_code))
		{
			exit_code %= 256;
		}
		else
		{
			printerr_three("exit", arg, "numeric argument required");
			exit_code = 255;
		}
	}
	rl_clear_history();
	free_env_list(shell);
	free_cmd_list(cmd);
	exit(exit_code);
}
