/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:51:52 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/11 16:38:43 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* parse arg str to */
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

static char	*replace_env_vars(t_shell *shell, char *input_cmd, int quoted, t_env *env)
{
	char	*res;
	int		i;
	int		start;
	char	*env_key;
	char	*env_val;
	char	*tmp;

	int		quote;

	res = ft_strdup("");
	i = 0;
	quote = 0;
	while (input_cmd[i])
	{
		// works with quotes
		if (!quote && (input_cmd[i] == '\'' || input_cmd[i] == '"'))
			quote = input_cmd[i];
		else if (input_cmd[i] == quote)
			quote = 0;
		// work with env vars
		if (input_cmd[i] == '$' && input_cmd[i + 1] && ft_isalnum(input_cmd[i + 1]) && quote != '\'')
		{
			start = ++i;
			while (ft_isalnum(input_cmd[i]) || input_cmd[i] == '_')
				i++;
			env_key = ft_substr(input_cmd, start, i - start);
			env_val = get_env_val(env, env_key);
			free(env_key);
			if (env_val != NULL)
			{
				tmp = res;
				res = ft_strjoin(res, env_val);
				free(tmp);
			}
		}
		// word with $?
		else if (input_cmd[i] == '$' && input_cmd[i + 1] && input_cmd[i + 1] == '?' && quote != '\'')
		{
			env_val = ft_itoa(shell->exec_result);
			if (env_val != NULL)
			{
				tmp = res;
				res = ft_strjoin(res, env_val);
				free(tmp);
			}
			free(env_val);
			i += 2;
		}
		else
		{
			res = str_append_char_safe(res, input_cmd[i++]);
		}
	}
	if (res[0] == '\0' && quoted)
	{
		free(res);
		return (NULL);
	}
	return (res);
}

char	**interpret_cmd_args(t_command *cmd, t_shell *shell)
{
	char	**argv;
	char	*str;
	int		i;
	int		j;
	char	**parts;

	argv = NULL;
	i = -1;
	while (++i < cmd->args_count)
	{
		if (!cmd->args[i].quoted && str_contains(cmd->args[i].arg, '*') && !cmd->args[i].interpet_env_var)
		{
			// cmd->args[i].quoted always 0
			argv = replace_wildcards(cmd->args[i].arg, argv);
		}
		else if (cmd->args[i].interpet_env_var)
		{
			str = replace_env_vars(shell, cmd->args[i].arg, cmd->args[i].quoted, shell->env_list);
			str = clear_quotes(str);
			parts = ft_split(str, ' ');
			free(str);
			j = -1;
			while (parts && parts[++j])
			{
				if (!cmd->args[i].quoted && str_contains(parts[j], '*'))
					argv = replace_wildcards(parts[j], argv);
				else if (parts[j][0] != '\0' || cmd->args[i].quoted)
					argv = str_arr_append(argv, ft_strdup(parts[j]));
			}
			free_split(parts);
		}
		else
		{
			str = ft_strdup(cmd->args[i].arg);
			str = clear_quotes(str);
			argv = str_arr_append(argv, str);
		}
	}
	cmd->argv = argv;
	cmd->argc = get_args_count(argv);
	if (ft_strcmp(cmd->cmd->arg, cmd->argv[0]) != 0)
	{
		free(cmd->cmd->arg);
		cmd->cmd->arg = cmd->argv[0];
	}
	return (argv);
}
