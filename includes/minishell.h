/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:46:32 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/05 19:54:13 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <string.h>

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
int		exec_cmd(t_command *cmd, t_shell *shell);

int		exec_bin(t_command *cmd, t_shell *shell);

int		exec_builtin(t_command *cmd, t_shell *shell);

int		is_builtin(t_command *cmd);

/* builtins */
int		safe_shell_exit(t_command *cmd, t_shell *shell);

int		echo(t_command *cmd, t_shell *shell);

int		print_env_list(t_command *cmd, t_shell *shell);

int		change_dir(t_command *cmd, t_shell *shell);

int		print_working_dir(t_command *cmd, t_shell *shell);

int		unset_env(t_command *cmd, t_shell *shell);

int		export_env(t_command *cmd, t_shell *shell);

/* env.c */
void	init_env_list(t_shell *shell, char **env);

void	free_env_list(t_shell *shell);

char	*get_env_val(t_env *env_list, char *key);

void	set_env_val(t_env *env_list, char *key, char *new_val);

void	del_env_pair(t_env **env_list, char *key);

void	print_export_env(t_env *env);

int		envlen(t_env *env);

int		env_contains(t_env *env, char *key);

char	**env_list_to_str_arr(t_env *env);

/* signal.c */
void	setup_signals(void);

/* utils.c */
int		get_args_count(char **args);

int		ft_strlen(char *str);

int		ft_strcmp(const char *s1, const char *s2);

int		ft_strncmp(const char *s1, const char *s2, int n);

char	*get_shell_prompt(t_shell *shell);

char	*ft_strcpy(char *str);

char	**ft_split(const char *str, char c);

char	*ft_strdup(const char *str);

char	*ft_strjoin(char *s1, char *s2);

void	free_split(char **split);

void	*ft_memcpy(void *dest, const void *src, size_t n);

int		str_contains(char *str, char c);

char	*ft_strchr(const char *s, int c);

char	*ft_substr(char *s, unsigned int start, size_t len);

int		ft_isalnum(int c);

int		ft_atoi(const char *str);

int		ft_isdigit(int c);

int		digits_only(char *str);

char	*ft_itoa(int n);

/* interpret args*/
char	**interpret_cmd_args(t_command *cmd, t_shell *shell);

#endif
