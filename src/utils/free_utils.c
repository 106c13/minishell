#include <stdlib.h>

void	free_argv(int argc, char **argv)
{
	int		i;

	i = -1;
	while (++i < argc)
	{
		if (argv[i])
			free(argv[i]);
	}
}
