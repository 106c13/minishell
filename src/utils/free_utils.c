#include <stdlib.h>
#include "minishell.h"

void	free_argv(char **argv)
{
	int		i;

	i = -1;
	while (argv[++i])
	{
		if (argv[i])
			free(argv[i]);
	}
	free(argv);
}

void	free_dict(t_dict *dict)
{
	t_dict	*tmp;

	while (dict)
	{
		tmp = dict;
		dict = dict->next;
		free(tmp->key);
		free(tmp->val);
		free(tmp);
	}
}
