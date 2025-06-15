/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 19:41:32 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/15 19:42:26 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_arg *arr, int len);

static t_arg	*append_split_args(t_arg *new_args, char *str, int *count)
{
	int		i;
	char	**split;
	t_arg	new;

	split = ft_split(str, ' ');
	i = 0;
	while (split && split[i])
	{
		if (split[i][0] != '\0')
		{
			new.str = ft_strdup(split[i]);
			new.interpret_env_var = 0; 
			new.quoted = 0; 
			new.file = 0;
			new.append = 0;
			new_args = append_arg(new, new_args, count);
		}
		i++;
	}
	free_split(split);
	return (new_args);
}

void	expand_args(t_command *cmd, t_shell *shell)
{
	t_arg	*new_args;
	int		new_args_count;
	char	*expanded_str;
	int		i;
	t_arg	*old_arg;
	t_arg	new;

	new_args = NULL;
	new_args_count = 0;
	i = -1;
	while (++i < cmd->args_count)
	{
		old_arg = &cmd->args[i];
		if (!old_arg->quoted && str_contains(old_arg->str, '*'))
		{
			new_args = replace_wildcards(old_arg, new_args, &new_args_count);
		}
		else if (old_arg->interpret_env_var)
		{
			expanded_str = replace_env_vars(shell, old_arg->str, old_arg->quoted);
			expanded_str = clear_quotes(expanded_str);
			if (!old_arg->quoted && str_contains(expanded_str, '*'))
			{
				new = (t_arg){
					.str = expanded_str,
					.interpret_env_var = 0,
					.quoted = 0,
					.file = old_arg->file,
					.append = old_arg->append
				};
				new_args = replace_wildcards(&new, new_args, &new_args_count);
				free(expanded_str);
			}
			else if (old_arg->quoted)
			{
				new = (t_arg){
					.str = expanded_str,
					.interpret_env_var = 0,
					.quoted = 0,
					.file = old_arg->file,
					.append = old_arg->append
				};
				new_args = append_arg(new, new_args, &new_args_count);
			}
			else
			{
				new_args = append_split_args(new_args, expanded_str, &new_args_count);
				free(expanded_str);
			}
		}
		else
		{
			expanded_str = ft_strdup(old_arg->str);
			expanded_str = clear_quotes(expanded_str);
			new = (t_arg){
				.str = expanded_str,
				.interpret_env_var = 0,
				.quoted = 0,
				.file = old_arg->file,
				.append = old_arg->append
			};
			new_args = append_arg(new, new_args, &new_args_count);

		}
	}
	free_args(cmd->args, cmd->args_count);
	cmd->args = new_args;
	cmd->args_count = new_args_count;

	cmd->argv = args_to_argv(new_args, new_args_count);
	cmd->argc = get_args_count(cmd->argv);
	cmd->cmd = &cmd->args[0];
	return ;
}
