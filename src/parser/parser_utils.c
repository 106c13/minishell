#include "minishell.h"

char	*trim_spaces(char *str)
{
	int	size;

	while (*str == ' ')
		str++;
	size = ft_strlen(str) - 1;
	while (str[size] == ' ')
		size--;
	str[size + 1] = '\0';
	return (str);
}

int	get_operator_type(char *word)
{
	if (ft_strcmp(word, "&") == 0)
		return (1);
	if (ft_strcmp(word, "|") == 0)
		return (2);
	if (ft_strcmp(word, "&&") == 0)
		return (3);
	if (ft_strcmp(word, "||") == 0)
		return (4);
	return (0);
}

void	free_command(t_command *cmd)
{
	t_command *tmp;

	while (cmd)
	{
		tmp = cmd;
		free(cmd->cmd);
		free(cmd->args);
		cmd = tmp->next;
		free(tmp);
	}
}

t_command	*create_command()
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command) * 1);
	if (!cmd)
		return (NULL);
	cmd->cmd = NULL;
	cmd->args = NULL;
	cmd->next = NULL;
	cmd->oper = 0;
	return (cmd);
}
