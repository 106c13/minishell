/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:51:52 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/05 16:57:01 by haaghaja         ###   ########.fr       */
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

static char	*replace_env_vars(char *input_cmd, int quoted, t_env *env)
{
	char	*res;
	int		i;
	int		start;
	char	*env_key;
	char	*env_val;
	char	*tmp;

	res = ft_strdup("");
	i = 0;
	while (input_cmd[i])
	{
		if (input_cmd[i] == '$' && input_cmd[i + 1] && ft_isalnum(input_cmd[i + 1]))
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

/* Count how many valid args in arr */
static int	count_valid_args(t_command *cmd, t_env *env)
{
	int		count;
	int		i;
	char	*expanded;
	t_arg	*arg;

	count = 0;
	i = 0;
	while (i < cmd->args_count)
	{
		arg = &cmd->args[i];
		if (!arg->interpet_env_var)
			count++;
		else
		{
			expanded = replace_env_vars(arg->arg, arg->quoted, env);
			if (expanded)
			{
				if (expanded[0] != '\0' || arg->quoted)
					count++;
				free(expanded);
			}
		}
		i++;
	}
	return (count);
}

char	**interpret_cmd_args(t_command *cmd, t_shell *shell)
{
	char	**argv;
	char	*expanded;
	int		argc;
	int		i;

	// change
	cmd->argc = count_valid_args(cmd, shell->env_list) ;
	argv = malloc(sizeof(char *) * (cmd->argc + 1));
	if (!argv)
		return (NULL);
	i = -1;
	argc = 0;
	while (++i < cmd->args_count)
	{
		if (cmd->args[i].interpet_env_var)
		{
			expanded = replace_env_vars(cmd->args[i].arg, quoted, shell->env_list);
			if (expanded && (expanded[0] != '\0' || quoted))
				argv[argc++] = clear_quotes(expanded);
			else
				free(expanded); // NULL or useless → skip
		}
		else
		{
			argv[argc] = ft_strdup(cmd->args[i].arg);
			argv[argc] = clear_quotes(argv[argc]);
			argc++;
		}
	}
	cmd->argv = argv;
	if (ft_strcmp(cmd->cmd->arg, cmd->argv[0]) != 0)
	{
		free(cmd->cmd->arg);
		cmd->cmd->arg = cmd->argv[0];
	}
	return (argv);
}
