/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:19 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/03 20:10:33 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct	s_arg
{
	char	*arg;
	int		interpet_env_var;
	char	quoted;
}	t_arg;

typedef struct s_command
{
	t_arg				*cmd;
	int					args_count;
	t_arg				*args;
	int					oper;
	struct s_command	*next;
}	t_command;

t_command	*parse_command(char *cmd);

t_command	*create_command(void);

void		free_command(t_command *cmd);

char		*get_word(char	**str);

char		*trim_spaces(char *str);

void		shell_split(char **str, t_command *cmd);

int			get_operator_type(char *word);

int	validate(char *input);
#endif
