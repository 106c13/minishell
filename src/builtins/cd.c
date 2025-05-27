#include "minishell.h"

int	change_directory(char *dir)
{
	if (chdir(dir) != 0)
	{
		printf("minishell: cd: %s: No such file or directory\n", dir);
		return (1);
	}
	return (0);
}
