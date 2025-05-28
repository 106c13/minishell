#include "minishell.h"

int	ft_strlen(char *str)
{
	int	size;

	size = 0;
	while (str[size])
	{
		size++;
	}
	return (size);
}

char	*get_shell_prompt(t_shell *shell)
{
	char	*shell_prompt;
	char	*path;
	char	*base;
	int		size;

	base = "minishell:";
//	getcwd();
	path = get_env_val(shell->env_list, "PWD");
	size = 0;
	size = ft_strlen(base) + ft_strlen(path);
	shell_prompt = malloc((size + 3) * sizeof(char));
	if (shell_prompt == NULL)
		return (NULL);
	// TODO: Fix this
	shell_prompt[size] = '>';
	shell_prompt[size + 1] = ' ';
	shell_prompt[size + 2] = '\0';
	ft_memcpy(shell_prompt, base, ft_strlen(base));
	ft_memcpy((shell_prompt + ft_strlen(base)), path, ft_strlen(path));
	return (shell_prompt);
}

int	get_args_count(char **args)
{
	int	count;

	if (args == NULL)
		return (0);
	count = 0;
	while (args[count])
		count++;
	return (count);
}
