/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:21:00 by haaghaja          #+#    #+#             */
/*   Updated: 2025/05/28 18:24:04 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char	*str)
{
	int	size;
	char	*dest;

	size = ft_strlen(str);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (NULL);
	dest[size] = '\0';
	while (size >= 0)
	{
		size--;
		dest[size] = str[size];
	}
	return (dest);
}
