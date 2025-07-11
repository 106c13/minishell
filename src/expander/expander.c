/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:41:32 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/24 19:17:03 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*split_and_append(char *str, t_arg *ref, t_arg *new_args, int *count);

static t_arg	*handle_expanded_str(
		char *expanded, t_arg *old, t_arg *new_args, int *new_count)
{
	t_arg	new;

	if (!old->quoted && str_contains(expanded, '*'))
	{
		new = new_arg_copy(expanded, old);
		new_args = replace_wildcards(&new, new_args, new_count);
	}
	else if (old->quoted)
	{
		new = new_arg_copy(ft_strdup(expanded), old);
		new_args = append_arg(new, new_args, new_count);
	}
	else
	{
		new_args = split_and_append(expanded, old, new_args, new_count);
	}
	return (new_args);
}

static t_arg	*expand_arg(
	t_arg *old, t_arg *new_args, int *new_count, t_shell *shell)
{
	char	*expanded;
	t_arg	new;

	if (!old->quoted && str_contains(old->str, '*'))
	{
		new_args = replace_wildcards(old, new_args, new_count);
	}
	else if (old->interpret_env_var)
	{
		expanded = replace_env_vars(shell, old->str, old->quoted);
		expanded = clear_quotes(expanded);
		new_args = handle_expanded_str(expanded, old, new_args, new_count);
		free(expanded);
	}
	else
	{
		expanded = ft_strdup(old->str);
		expanded = clear_quotes(expanded);
		new = new_arg_copy(expanded, old);
		new_args = append_arg(new, new_args, new_count);
	}
	return (new_args);
}

void	find_cmd(t_command *cmd)
{
	int	i;

	i = 0;
	cmd->cmd = NULL;
	while (i < cmd->args_count)
	{
		if (cmd->args[i].file == 0)
		{
			cmd->cmd = &cmd->args[i];
			break ;
		}
		i++;
	}
}

void	expand_args(t_command *cmd, t_shell *shell)
{
	t_arg	*new_args;
	int		new_count;
	int		i;
	t_arg	*old;

	new_args = NULL;
	new_count = 0;
	i = 0;
	while (i < cmd->args_count)
	{
		old = &cmd->args[i];
		new_args = expand_arg(old, new_args, &new_count, shell);
		i++;
	}
	free_args(cmd->args, cmd->args_count);
	cmd->args = new_args;
	cmd->args_count = new_count;
	find_cmd(cmd);
	cmd->argv = args_to_argv(new_args, new_count);
	cmd->argc = get_args_count(cmd->argv);
}
