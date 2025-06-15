/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */ /*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:51:52 by azolotar          #+#    #+#             */ /*   Updated: 2025/06/14 16:36:59 by azolotar         ###   ########.fr       */
/*                                                                            */ /* ************************************************************************** */
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
	while (i < args_count)
	{
		if (args[i].file == 0)
			argc += 1;
		i++;
	}
	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	i = 0;
	j = 0;
	while (i < args_count)
	{
		if (args[i].file == 0)
		{
			argv[j] = ft_strdup(args[i].str);
			// handle bla bla bla
			j++;
		}
		i++;
	}
	argv[j] = NULL;
	return (argv);
}

void	expand_cmd_args(t_command *cmd, t_shell *shell)
{
	t_arg	*new_args;
	int		new_args_count;
	char	*expanded_str;
	int		i;
	t_arg	*old_arg;

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
				t_arg new = {
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
				t_arg new = {
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
			t_arg new = {
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
	print_cmd(cmd);
	return ;
}
