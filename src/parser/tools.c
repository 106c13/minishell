/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:11:44 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/05 16:54:36 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*clear_quotes(char *str)
{
	char	*nstr;
	char	quote;
	int		size;
	int		i;

	quote = 0;
	i = 0;
	if (!str)
		return (NULL);
	size = get_unquoted_len(str);
	nstr = malloc(sizeof(char) * (size + 1));
	if (!nstr)
		return (NULL);
	nstr[size] = '\0';
	size = 0;
	while (str[size])
	{
		if (!quote && (str[size] == '\'' || str[size] == '"'))
			quote = str[size];
		else if (str[size] == quote)
			quote = 0;
		else
		{
			nstr[i] = str[size];
			i++;
		}
		size++;
		
	}
	free(str);
	return (nstr);
}
