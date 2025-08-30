#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "utils.h"
#include "defines.h"

int	alias(t_ast *cmd, t_dict **aliases)
{
	char	*key;
	char	*val;
	
	if (cmd->argc == 1)
		return (print_dict(*aliases), SUCCESS);
	val = ft_strchr(cmd->argv[1], '=');
	if (val)
		*val++ = '\0';
	else
		return (FAILURE);
	key = cmd->argv[1];
	*aliases = set_dict_val(*aliases, key, val);
	return (SUCCESS);
}
