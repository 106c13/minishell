/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:46:32 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/27 19:09:34 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

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
int	exec_cmd(char *cmd, t_shell *shell);

int	exec_bin(char *cmd, t_shell *shell);

int	exec_builtin(char *cmd, t_shell *shell);

int	is_builtin(char *cmd);

/* buitins */
int		safe_shell_exit(t_shell *shell);

int		echo(char **args, t_shell *shell);

int		print_env_list(t_shell *shell);

/* env.c */
void	init_env_list(t_shell *shell, char **env);

void	free_env_list(t_shell *shell);

char	*get_env_val(t_env *env_list, char *key);

/* signal.c */
void	setup_signals(void);

/* utils.c */
int		ft_strlen(char *str);

char	*get_shell_prompt(t_shell *shell);

char	**ft_split(const char *str, char c);

int		get_split_count(const char *str, char c);

void	free_split(char **split);

char	*ft_strdup(const char *str);

int		ft_strcmp(const char *s1, const char *s2);

char	*ft_strjoin(char *s1, char *s2);

void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
