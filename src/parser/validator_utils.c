/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 17:24:47 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 17:43:03 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quote(char *str, int i)
{
	char	quote;

	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i])
		return (i);
	else
		return (-1);
}

int	has_content_inside(char *str, int start)
{
	int		i;
	int		has;

	i = start + 1;
	has = 0;
	while (str[i] && str[i] != ')')
	{
		if (!ft_isspace((unsigned char)str[i]) && str[i] != '(')
			has = 1;
		if (str[i] == '\'' || str[i] == '"')
			i = skip_quote(str, i);
		if (i == -1)
			return (0);
		i++;
	}
	if (!str[i] || !has)
		return (0);
	return (1);
}

int	check_double_op(char *str, int *i)
{
	*i += 2;
	while (str[*i] && ft_isspace((unsigned char)str[*i]))
		(*i)++;
	if (!str[*i] || str[*i] == ')' || str[*i] == '|' || str[*i] == '&')
		return (0);
	return (1);
}

int	check_single_pipe(char *str, int i)
{
	int	j;

	j = i + 1;
	while (str[j] && ft_isspace((unsigned char)str[j]))
		j++;
	if (!str[j] || str[j] == '|' || str[j] == '&' || str[j] == ')')
		return (0);
	return (1);
}
