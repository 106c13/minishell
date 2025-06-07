/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haaghaja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:46:19 by haaghaja          #+#    #+#             */
/*   Updated: 2025/06/05 17:08:18 by haaghaja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct	s_file
{
	char	*name;
	int	append;
	int		interpet_env_var;
	
}	t_file;

typedef struct	s_arg
{
	char	*arg;
	int		interpet_env_var;
	char	quoted;
}	t_arg;

typedef struct s_command
{
	t_arg				*cmd;
	t_arg				*args;
	t_arg				*output_files;
	int					args_count;
	int					files_count;
	char				**argv;
	int					argc;
	int					oper;
	struct s_command	*next;
}	t_command;



/* parser.c */ 
t_command	*parse_command(char *cmd);

/* utils.c */
t_command	*create_command(void);

void		free_command(t_command *cmd);

char		*trim_spaces(char *str);

int			get_operator_type(char *word);

int	get_unquoted_len(char	*stri);

/* shell_split.c */
void		shell_split(char **str, t_command *cmd);

/* validator.c */
int	validate(char *input);

/* tools.c */
char	*clear_quotes(char *str);

#endif
