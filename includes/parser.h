#ifndef	PARSER_H
# define PARSER_H

typedef struct s_command
{
	char	*cmd;
	char	**args;
} t_command;

t_command	*parse_command(char *cmd);

char	*get_word(char	**str);

char	*trim_spaces(char *str);

#endif
