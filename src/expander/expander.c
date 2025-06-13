/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:51:52 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/13 19:59:50 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_exec_result(char *str, t_shell *shell)
{
	char	*val;
	char	*tmp;

	val = ft_itoa(shell->exec_result);
	tmp = str;
	str = ft_strjoin(str, val);
	free(tmp);
	free(val);
	return (str);
}

static char	*append_env_val(char *str, char *input_cmd, int *i, t_env *env)
{
	char	*tmp;
	int		start;
	char	*key;
	char	*val;

	start = ++(*i);
	while (ft_isalnum(input_cmd[*i]) || input_cmd[*i] == '_')
		(*i)++;
	key = ft_substr(input_cmd, start, *i - start);
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

char	*replace_env_vars(t_shell *shell, char *input_cmd, int quoted)
{
	char	*res;
	int		i;
	char	quote;

	res = ft_strdup("");
	i = 0;
	quote = 0;
	while (input_cmd[i])
	{
		if (quote == 0 && (input_cmd[i] == '\'' || input_cmd[i] == '"'))
			quote = input_cmd[i];
		else if (input_cmd[i] == quote)
			quote = 0;
		if (input_cmd[i] == '$' && input_cmd[i + 1] && quote != '\'')
		{
			if (input_cmd[i + 1] == '?')
			{
				res = append_exec_result(res, shell);
				i += 2;
			}
			else if (ft_isalnum(input_cmd[i + 1]))
			{
				res = append_env_val(res, input_cmd, &i, shell->env_list);
			}
		}
		else
			res = str_append_char_safe(res, input_cmd[i++]);
	}
	res = str_append_char_safe(res, '\0');
	if (res[0] == '\0' && quoted)
		return (free(res), NULL);
	return (res);
}

static char	**append_split(char **argv, char *str)
{
	int		i;
	char	**split;

	split = ft_split(str, ' ');
	i = 0;
	while (split && split[i])
	{
		if (split[i][0] != '\0')
			argv = str_arr_append(argv, ft_strdup(split[i]));
		i++;
	}
	free_split(split);
	return (argv);
}

char	**expand_cmd_args(t_command *cmd, t_shell *shell)
{
	char	**argv;
	char	*str;
	int		i;
	t_arg	*arg;

	argv = NULL;
	i = -1;
	while (++i < cmd->args_count)
	{
		arg = &cmd->args[i];
		if (!arg->quoted && str_contains(arg->arg, '*'))
			argv = replace_wildcards(arg->arg, argv);
		else if (arg->interpet_env_var)
		{
			str = replace_env_vars(shell, arg->arg, arg->quoted);
			str = clear_quotes(str);
			if (!arg->quoted && str_contains(str, '*'))
				argv = replace_wildcards(str, argv);
			else if (cmd->args[i].quoted)
				argv = str_arr_append(argv, str);
			else
				argv = append_split(argv, str);
			free(str);
		}
		else
		{
			str = ft_strdup(cmd->args[i].arg);
			str = clear_quotes(str);
			argv = str_arr_append(argv, str);
			free(str);
		}
	}
	cmd->argv = argv;
	cmd->argc = get_args_count(argv);
	if (ft_strcmp(cmd->cmd->arg, cmd->argv[0]) != 0)
	{
		free(cmd->cmd->arg);
		cmd->cmd->arg = ft_strdup(cmd->argv[0]);
	}
	return (argv);
}
