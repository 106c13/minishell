#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include "utils.h"

int	get_redirs_size(t_redir *redirs)
{
	int	size;

	size = 0;
	while (redirs->type)
	{
		size++;
		redirs++;
	}
	return (size);
}

char	*get_prompt()
{
	char			*new;
	char			*arr[6];

	arr[3] = getcwd(NULL, 0);
	if (!arr[3])
	{
		printf("minishell: prompt: can't get the path\n");
		return ("minishell > ");
	}
	arr[1] = getlogin();
	if (!arr[1])
	{
		printf("minishell: prompt: can't get the username\n");
		return ("minishell > ");
	}
	arr[0] = "\033[91m";
	arr[2] = "\033[0m@\033[94mminishell \033[92m";
	arr[4] = "\033[31m ❯ \033[0m";
	arr[5] = NULL;
	new = ft_nstrjoin(arr);
	if (!new)
		return (free(arr[3]), "minishell > ");
	free(arr[3]);
	return (new);
}
