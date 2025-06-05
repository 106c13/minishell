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
	if (ft_strncmp(word, "&&", 2) == 0)
		return (AND);
	if (ft_strncmp(word, "||", 2) == 0)
		return (OR);
	if (ft_strncmp(word, "&", 1) == 0)
		return (BG);
	if (ft_strncmp(word, "|", 1) == 0)
		return (PIPE);
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

int	get_unquoted_len(char	*str)
{
	char	quote;
	int		size;

	size = 0;
	quote = 0;
	while (*str)
	{
		if (!quote && (*str == '\'' || *str == '"'))
			quote = *str;
		else if (*str == quote)
			quote = 0;
		else
			size++;
		str++;
	}
	return (size);
}
