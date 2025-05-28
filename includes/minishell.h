/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:46:32 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/28 19:26:33 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "parser.h"
# include "defines.h"

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char	exec_result; // for $?
	t_env	*env_list;
}	t_shell;

/* exec */
int	exec_cmd(t_command *cmd, t_shell *shell);

int	exec_bin(t_command *cmd, t_shell *shell);

int	exec_builtin(t_command *cmd, t_shell *shell);

int	is_builtin(t_command *cmd);

/* builtins */
int		safe_shell_exit(t_shell *shell);

int		echo(char **args, t_shell *shell);

int		print_env_list(t_shell *shell);

int		change_dir(t_command *cmd, t_shell *shell);

int		print_working_dir(t_shell *shell);

int		clear_shell(void);

int		unset_env(t_command *cmd, t_shell *shell);

/* env.c */
void	init_env_list(t_shell *shell, char **env);

void	free_env_list(t_shell *shell);

char	*get_env_val(t_env *env_list, char *key);

void	set_env_val(t_env *env_list, char *key, char *new_val);

void	del_env_pair(t_env **env_list, char *key);

/* signal.c */
void	setup_signals(void);

/* utils.c */
int		get_args_count(char **args);

int		ft_strlen(char *str);

int		ft_strcmp(const char *s1, const char *s2);

char	*get_shell_prompt(t_shell *shell);

char	**ft_split(const char *str, char c);

char	*ft_strdup(const char *str);

char	*ft_strjoin(char *s1, char *s2);

void	free_split(char **split);

void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
