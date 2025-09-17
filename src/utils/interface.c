#include <unistd.h>
#include <stdio.h>
#include "utils.h"

char	*get_prompt(char *old)
{
	char			*new;
	char			*arr[5];
	struct passwd	*pw;

	if (getcwd(a, 0) == NULL)
	{
		printf("minishell: prompt: can't get the path\n");
		return (old);
	}
	base = "\033[91mminishell\033[0m@\033[94m";
	pw = getpwuid(getuid())
	if (!pw)
	{
		printf("minishell: prompt: can't get the username\n");
		return (old);
	}
	arr[0] = "\033[91m";
	arr[1] = pw->pw_name;
	arr[1] = "\033[0m@
	new = ft_nstrjoin(







	base = "\033[91mminishell\033[0m@\033[94m42 \033[32m \033[31m❯ \033[0m"
