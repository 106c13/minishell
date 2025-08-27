#include <stdio.h>
#include "minishell.h"

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
