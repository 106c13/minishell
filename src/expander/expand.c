#include <stdio.h>
#include <stdbool.h>
#include "minishell.h"
#include "expander.h"
#include "utils.h"

/* 
arg: abc$USER"blah" 
abc = chunk
$USER = variable
"blah" = quote
*/
char	*expand_arg(char *arg, t_shell *shell)
{
	char	*new_arg;

	arg = expand_speacial_character(arg, shell->env);
	if (!arg)
		return (NULL);
	new_arg = ft_calloc(1, 1);
	if (!new_arg)
		return (NULL);
	while (*arg)
	{
		if (is_quote(*arg))
			new_arg = expand_quotes(new_arg, &arg, shell);
		else if (*arg == '$')
			new_arg = expand_variable(new_arg, &arg, shell);
		else
			new_arg = add_chunk(new_arg, &arg, "'\"$");
		if (!new_arg)
			return (NULL);
	}
	return (new_arg);
}

t_redir	*expand_redirections(t_redir *redirs, t_shell *shell)
{
	t_redir	*new;
	int		size;
	int		i;

	if (!redirs)
		return (NULL);
	size = get_redirs_size(redirs);
	new = malloc(sizeof(t_redir) * (size + 1));
	i = 0;
	while (i < size)
	{
		new[i].type = redirs[i].type;
		new[i].file = expand_arg(redirs[i].file, shell);
		if (!new[i].file)
		{
			printf("minishell: %s: ambiguous redirect\n", redirs[i].file);
			free(new);
			free(redirs);
			return (NULL);
		}
		i++;
	}
	new[i].type = 0;
	free(redirs);
	return (new);
}

char	**expand_argv(int size, char **argv, t_shell *shell)
{
	char	**new;
	char	**tmp;
	char	*new_arg;
	int		i;

	i = -1;
	new = NULL;
	while (++i < size)
	{
		new_arg = expand_arg(argv[i], shell);
		if (!new_arg)
			return (free_argv(argv), NULL);
		if (i == 0)
		{
			tmp = split_command(new_arg);
			new = join_str_arrays(new, tmp);
		}
		else
			new = append_str_array(new, new_arg);
		if (!new)
			return (NULL);
	}
	free_argv(argv);
	return (new);
}

void	expand_command(t_ast	*leaf, t_shell *shell)
{
	int	argc;

	argc = 0;
	if (leaf->argv)
	{
		leaf->argv = expand_argv(leaf->argc, leaf->argv, shell);
		while (leaf->argv && leaf->argv[argc])
			argc++;
		leaf->argc = argc;
		// wildcard
	}
	if (leaf->redirs)
	{
		leaf->redirs = expand_redirections(leaf->redirs, shell);
		// wildcard
	}
}
