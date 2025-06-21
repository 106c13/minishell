/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:55:07 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 19:10:00 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_and_check(char *delimiter)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		printerr3("minishell: warning: here-document "
			"delimited by end-of-file (wanted `", delimiter, "`)");
		return (NULL);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
