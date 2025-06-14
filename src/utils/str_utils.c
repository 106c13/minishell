/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:47:11 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/14 13:48:38 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**str_arr_append(char **arr, char *str)
{
	char	**new_arr;
	int		len;
	int		i;

	if (arr == NULL)
		len = 0;
	else
		len = get_args_count(arr);
	new_arr = malloc(sizeof(char *) * (len + 2));
	if (!new_arr)
		return (arr);
	i = 0;
	while (i < len)
	{
		new_arr[i] = arr[i];
		i++;
	}
	if (arr != NULL)
		free(arr);
	new_arr[i++] = ft_strdup(str);
	new_arr[i] = NULL;
	return (new_arr);
}

char	*str_append_char_safe(char *str, char c)
{
	char	*new;
	int		len;

	len = ft_strlen(str);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	ft_memcpy(new, str, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(str);
	return (new);
}
