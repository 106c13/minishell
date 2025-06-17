/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:19 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/17 17:08:18 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_arg
{
	char	*str;
	int		interpret_env_var;
	char	quoted;

	char	file; /* 0 - not file, 1 - infile 2 - outfile */
	char	append; /* 0 or 1 */
}	t_arg;

typedef struct s_command
{
	t_arg				*cmd;

	t_arg				*args;
	int					args_count;
	int					out_file_count;
	int					in_file_count;

	char				**argv;
	int					argc;

	int					operator_type;
	char				*delimiter;
	int					depth;
	int					last_in_group;
	struct s_command	*next;
}	t_command;

/* parser.c */
t_command	*parse_command(char *cmd);

/* utils.c */
t_command	*create_command(void);

void		free_command(t_command *cmd);

char		*trim_spaces(char *str);

int			get_operator_type(char *word);

int			get_unquoted_len(char	*stri);

/* shell_split.c */
int			shell_split(char **str, t_command *cmd);

int			get_mode_type(char	*mode);

/* validator.c */
int			validate(char *input);

/* tools.c */
char		*clear_quotes(char *str);

int			setup_command(char *str, t_command *cmd);

/* helpers.c */
int			is_whitespace(char c);

int			is_quote(char c);

void		set_operator(char **str, t_command *cmd);

/* counter.c */
void		counter(char *str, t_command *cmd);

int			count_in_quotes(char *str);

int			count_in_file(char *str);

int			is_eow(char c);

#endif
