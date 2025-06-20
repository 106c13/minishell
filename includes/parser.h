/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:19 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/20 18:39:15 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_arg
{
	char	*str;
	int		interpret_env_var;
	char	quoted;

	int		depth;
	char	file;
	char	append;
}	t_arg;

typedef struct s_oper
{
	int	type;
	int	depth;
}	t_oper;

typedef struct s_command
{
	t_arg				*cmd;

	t_arg				*args;
	int					args_count;

	int					out_file_count;
	int					in_file_count;

	char				**delimiters;
	int					delimiter_count;
	int					heredoc_fd;

	char				**argv;
	int					argc;

	t_oper				op;

	int					last_in_group;
	int					depth;
	struct s_command	*next;
}	t_command;

/* parser.c */
t_command	*parse_command(char *cmd);

int			calculate_depth(char *src, char *dest);
/* parser_utils.c */
t_command	*create_command(void);

void		free_command(t_command *cmd);

char		*trim_spaces(char *str);

int			get_operator_type(char *word);

int			get_unquoted_len(char	*stri);

/* parser_utils1.c */
void		add_delimiter(char **str, t_command *cmd);

int			get_arg_len(char *str);

int			get_mode_type(char *mode);

/* shell_split.c */
int			shell_split(char **str, char *tmp, t_command *cmd);

int			get_mode_type(char	*mode);

/* validator.c */
int			validate(char *input);

/* tools.c */
char		*clear_quotes(char *str);

int			setup_command(char *str, t_command *cmd);

char		*ft_get_word(char **str);

/* helpers.c */
int			is_whitespace(char c);

int			is_quote(char c);

int			set_operator(char **str, t_command *cmd, char *start);

int			is_env(char *str);

/* counter.c */
void		counter(char *str, t_command *cmd);

int			count_in_quotes(char *str);

int			count_in_file(char *str);

int			is_eow(char c);

#endif
