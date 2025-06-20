/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:41:25 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 13:41:02 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "minishell.h"

static int	is_valid_number(char *str)
{
	int			i;
	int			sign;
	long long	n;

	i = 0;
	sign = 1;
	n = 0;
	if (!str || !*str)
		return (0);
	if ((str[i] == '-' || str[i] == '+') && str[i++] == '-')
		sign = -1;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		if (sign == 1 && n > (LLONG_MAX - (str[i] - '0')) / 10)
			return (0);
		if (sign == -1 && (-n < (LLONG_MIN + (str[i] - '0')) / 10))
			return (0);
		n = n * 10 + (str[i++] - '0');
	}
	return (1);
}

static long long	ft_strtoll(const char *str)
{
	int			sign;
	int			i;
	long long	result;

	sign = 1;
	i = 0;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	safe_shell_exit(t_command *cmd, t_shell *shell)
{
	long long	exit_code_ll;
	int			exit_code;
	char		*arg;

	exit_code = SUCCESS;
	printf("exit\n");
	if (cmd != NULL && cmd->argc >= 2 && !is_valid_number(cmd->argv[1]))
	{
		printerr_three("exit", cmd->argv[1], "numeric argument required");
		exit_code = 2;
	}
	else if (cmd != NULL && cmd->argc > 2)
		return (printerr_two("exit", "too many arguments"), FAILURE);
	else if (cmd != NULL && cmd->argc == 2)
	{
		arg = cmd->argv[1];
		if (!is_valid_number(arg))
		{
			printerr_three("exit", arg, "numeric argument required");
			exit_code = 2;
		}
		else
		{
			exit_code_ll = ft_strtoll(arg);
			exit_code = (int)(exit_code_ll % 256);
		}
	}
	cleanup(shell);
	exit(exit_code);
}
