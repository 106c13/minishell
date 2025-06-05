/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:52:21 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/05 19:51:30 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_divider(int n)
{
	int	div;

	div = 1000000000;
	while (n / div == 0)
	{
		div /= 10;
	}
	return (div);
}

static char	*create_result(char *buf)
{
	size_t	i;
	size_t	len;
	char	*result;

	len = ft_strlen(buf);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = buf[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	int		div;
	char	buf[12];
	int		i;

	i = 0;
	if (n < 0)
		buf[i++] = '-';
	if (n == 0)
		return (create_result("0"));
	div = get_divider(n);
	while (div != 0)
	{
		if (n < 0)
			buf[i] = (n / div) * -1 + '0';
		else
			buf[i] = n / div + '0';
		n %= div;
		div /= 10;
		i++;
	}
	buf[i] = '\0';
	return (create_result(buf));
}

/* #include <limits.h>
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_itoa(-613));
	return (0);
} */
