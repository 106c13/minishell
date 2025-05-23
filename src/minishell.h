/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:46:32 by azolotar          #+#    #+#             */
/*   Updated: 2025/05/22 21:36:20 by azolotar         ###   ########.fr       */
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
	t_env	*env_list;
}	t_shell;

/* env.c */
void	init_env_list(t_shell *shell, char **env);

void	free_env_list(t_shell *shell);

char	*get_env_val(t_env *env_list, char *key);

/* signal.c */
void	setup_signals(void);

/* utils.c */
int		ft_strlen(char *str);

char	*get_shell_prompt(t_shell *shell);

/* ft_split.c */
char	**ft_split(const char *str, char c);

int		get_split_count(const char *str, char c);

void	free_split(char **split);

/* ft_strdub.c */
char	*ft_strdup(const char *str);

/* ft_strcmp.c */
int		ft_strcmp(const char *s1, const char *s2);

/* ft_strjoin */
char	*ft_strjoin(char *s1, char *s2);

/* ft_memcpy */
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
