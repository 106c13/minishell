/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:41:25 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 16:17:35 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "minishell.h"

static bool	is_long_long(long long num, int digit, int sign)
{
	if (sign == 1)
	{
		if (num > (LLONG_MAX - digit) / 10)
			return (false);
	}
	else
	{
		if (-num < (LLONG_MIN + digit) / 10)
			return (false);
	}
	return (true);
}

static int	parse_exit_code(char *str)
{
	long long	num;
	int			result;
	int			sign;

	num = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-') sign = -1;
	if (!*str)
		return (2);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (2);
		if (!is_long_long(num, (*str - 48), sign))
			return (2);
		num = num * 10 + (*str - 48);
		str++;
	}
	result = num % 256;
	return (result);
}

int	shell_exit(t_ast *leaf)
{
	int			exit_code;

	if (leaf->argc > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (leaf->argc == 1)
		exit(0);
	exit_code = parse_exit_code(leaf->argv[1]);
	if (exit_code == 2)
		printf("minishell: exit: %s numeric argument required\n", leaf->argv[1]);
	exit(exit_code);
}
