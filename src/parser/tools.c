/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:11:44 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/25 21:40:53 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init(char *quote, int *i, char *kost, int *size)
{
	*quote = 0;
	*i = 0;
	*kost = 0;
	*size = -1;
}

char	*clear_quotes(char *str)
{
	char	*nstr;
	char	quote;
	char	kost;
	int		size;
	int		i;

	init(&quote, &i, &kost, &size);
	nstr = malloc(sizeof(char) * (get_unquoted_len(str) + 1));
	if (!nstr)
		return (NULL);
	while (str[++size])
	{
		if (!kost && str[size] == KOSTYL)
			kost = 1;
		else if (str[size] == KOSTYL)
			kost = 0;
		else if (!quote && is_quote(str[size]) && !kost)
			quote = str[size];
		else if (str[size] == quote && !kost)
			quote = 0;
		else
			nstr[i++] = str[size];
	}
	nstr[i] = '\0';
	return (free(str), nstr);
}

int	setup_command(char *str, t_command *cmd)
{
	counter(str, cmd);
	cmd->args = malloc(sizeof(t_arg) * (cmd->args_count));
	if (!cmd->args)
		return (1);
	cmd->delimiters = malloc(sizeof(char *) * (cmd->delimiter_count + 1));
	if (!cmd->delimiters)
	{
		free(cmd->args);
		return (1);
	}
	cmd->delimiters[0] = NULL;
	cmd->cmd = cmd->args;
	return (0);
}

char	*ft_get_word(char **str)
{
	int		size;
	int		i;
	char	*word;

	size = get_arg_len(*str);
	i = 0;
	word = malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	while (i < size)
	{
		word[i++] = **str;
		(*str)++;
	}
	word[size] = '\0';
	return (word);
}
