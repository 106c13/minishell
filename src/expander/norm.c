/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:34:29 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/25 21:31:12 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(char **res, int *i, char *quote)
{
	*res = ft_strdup("");
	*i = 0;
	*quote = 0;
}

char	*add_quotes(char *str)
{
	int		len;
	char	*new;

	len = ft_strlen(str);
	new = malloc(sizeof(char) * (len + 3));
	if (!new)
		return (NULL);
	new[0] = 31;
	ft_memcpy(new + 1, str, len);
	new[len + 1] = 31;
	new[len + 2] = '\0';
	free(str);
	return (new);
}
