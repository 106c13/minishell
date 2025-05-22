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
# define  MINISHELL_H

typedef struct	s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}	t_env;

typedef struct	s_shell
{
	t_env	*env_list;
}	t_shell;

/* env.c */
void	init_env_list(t_shell *shell, char **env);

void	free_env_list(t_shell *shell);

/* signal.c */
void	setup_signals(void);

/* ft_split.c */
char	**ft_split(const char *str, char c);

int		get_split_count(const char *str, char c);

void	free_split(char **split);

/* ft_strdub.c */
char	*ft_strdup(const char *str);
#endif
