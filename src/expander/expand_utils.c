/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:48:18 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/20 18:20:50 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_exec_result(char *str, t_shell *shell, int *i)
{
	char	*val;
	char	*tmp;

	val = ft_itoa(shell->exec_result);
	tmp = str;
	str = ft_strjoin(str, val);
	free(tmp);
	free(val);
	*i += 2;
	return (str);
}

static char	*append_env_val(char *str, char *cmd_str, int *i, t_env *env)
{
	char	*tmp;
	int		start;
	char	*key;
	char	*val;

	start = ++(*i);
	while (ft_isalnum(cmd_str[*i]) || cmd_str[*i] == '_')
		(*i)++;
	key = ft_substr(cmd_str, start, *i - start);
	val = get_env_val(env, key);
	free(key);
	if (val != NULL)
	{
		tmp = str;
		str = ft_strjoin(str, val);
		free(tmp);
	}
	return (str);
}

static char	setup_quote(char *cmd_str, char quote, int i)
{
	if (quote == 0 && (cmd_str[i] == '\'' || cmd_str[i] == '"'))
		return (cmd_str[i]);
	else if (cmd_str[i] == quote)
		return (0);
	else
		return (quote);
}

char	*replace_env_vars(t_shell *shell, char *cmd_str, int quoted)
{
	char	*res;
	int		i;
	char	quote;

	res = ft_strdup("");
	i = 0;
	quote = 0;
	while (cmd_str[i])
	{
		quote = setup_quote(cmd_str, quote, i);
		if (cmd_str[i] == '$' && cmd_str[i + 1] && quote != '\'')
		{
			if (cmd_str[i + 1] == '?')
				res = append_exec_result(res, shell, &i);
			else if (cmd_str[i + 1] == '_' || ft_isalnum(cmd_str[i + 1]))
				res = append_env_val(res, cmd_str, &i, shell->env_list);
			else
				res = str_append_char_safe(res, cmd_str[i++]);
		}
		else
			res = str_append_char_safe(res, cmd_str[i++]);
	}
	res = str_append_char_safe(res, '\0');
	if (res[0] == '\0' && quoted)
		return (free(res), NULL);
	return (res);
}

int	count_not_files_args(t_arg *args, int args_count);

char	**args_to_argv(t_arg *args, int args_count)
{
	char	**argv;
	int		i;
	int		argc;
	int		j;

	if (!args || args_count == 0)
		return (NULL);
	argc = 0;
	i = 0;
	argc = count_not_files_args(args, args_count);
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < args_count)
	{
		if (args[i].file == 0)
			argv[++j] = ft_strdup(args[i].str);
	}
	argv[argc] = NULL;
	return (argv);
}
