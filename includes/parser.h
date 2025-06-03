/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:19 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/03 17:22:18 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PARSER_H
# define PARSER_H

typedef struct s_command
{
	char			*cmd;
	char			**args;
	int				oper;	
	struct s_command	*next;
} t_command;

typedef struct	s_arg
{
	char	*arg;
	char	interpet_env_var;
}	t_arg;

t_command	*parse_command(char *cmd);

void		free_command(t_command *cmd);

char		*get_word(char	**str);

char		*trim_spaces(char *str);

char	**shell_split(char *str, char c);

int	get_operator_type(char *word);
#endif
