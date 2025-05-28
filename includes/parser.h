#ifndef	PARSER_H
# define PARSER_H

typedef struct s_command
{
	char				*cmd;
	char				**args;
	struct s_command	*next;
} t_command;

t_command	*parse_command(char *cmd);

void		free_command(t_command *cmd);

char		*get_word(char	**str);

char		*trim_spaces(char *str);

#endif
