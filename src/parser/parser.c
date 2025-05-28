#include "minishell.h"


// ONLY for tests
void	print_cmd(t_command *cmd)
{
	int	i;

	i = 0;
	printf("CMD: %s\n", cmd->cmd);
	while (cmd->args[i])
	{
		printf("ARG %d: %s\n", i + 1, cmd->args[i]);
		i++;  
	}
}


t_command	*parse_command(char *input)
{
	t_command	*cmd;

	input = trim_spaces(input);
	if (*input == '\0')
		return (NULL);
	cmd = malloc(sizeof(t_command) * 1);
	// add malloc check
	cmd->cmd = get_word(&input);
	cmd->args = ft_split(input, ' ');
	print_cmd(cmd);
	return (cmd);
}


void	free_command(t_command *cmd)
{
	// also free args
	free(cmd);
}
