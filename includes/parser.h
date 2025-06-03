/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:19 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/03 17:10:48 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_command
{
	char				*cmd;
	char				**args;
	char				**outfiles;
	int					oper;
	struct s_command	*next;
}	t_command;

t_command	*parse_command(char *cmd);

t_command	*create_command(void);

void		free_command(t_command *cmd);

char		*get_word(char	**str);

char		*trim_spaces(char *str);

char		**shell_split(char *str, char c);

int			get_operator_type(char *word);
#endif
