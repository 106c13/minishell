#include <stdlib.h>
#include <stdbool.h>
#include "minishell.h"
#include "enviroment.h"
#include "utils.h"

//TODO: make new group of function for special characters ~
//This works only for ~
char	*expand_speacial_character(char *arg, t_list *env)
{
	char	*new;
	char	*home;

	if (*arg != '~' || (arg[1] && arg[1] != '/'))
		return (arg);
	home = get_env_val(env, "HOME");
	if (!home)
		return (arg);
	new = ft_strjoin(home, &arg[1]);
	if (!new)
		return (NULL);
	return (new);
}

char	*parse_env_key(char *str)
{
	char	*key;
	int		size;

	size = 0;
	str++;
	while (str[size] && (ft_isalnum(str[size]) || str[size] == '_'))
			size++;
	if (size == 0)
		return (NULL);
	key = malloc(size + 1);
	if (!key)
		return (NULL);
	key = ft_memcpy(key, str, size);
	key[size] = '\0';
	return (key);
}

char	*expand_variable(char *dest, char **src, t_shell *shell)
{
	char	*key;
	char	*value;
	char	*new_dest;

	if ((*src)[1] == '?')
	{
		*src += 2;
		new_dest = ft_strjoin(dest, ft_itoa(shell->exec_result));
		free(dest);
		return (new_dest);
	}
	else if ((*src)[1] == '$')
	{
		*src += 2;
		new_dest = ft_strjoin(dest, ft_itoa(shell->pid));
		free(dest);
		return (new_dest);
	}
	key = parse_env_key(*src);
	if (!key)
		return (free(dest), NULL);
	value = get_env_val(shell->env, key);
	if (!value)
		value = "";
	*src += ft_strlen(key) + 1;
	dest = ft_strjoin(dest, value);
	free(key);
	return (dest);
}

char	*add_chunk(char *dest, char **src, char *delim)
{
	char	*new_dest;
	int		i;

	i = 0;
	while ((*src)[i] && !is_end((*src)[i], delim))
		i++;
	new_dest = ft_strnjoin(dest, *src, i);
	free(dest);
	*src += i;
	return (new_dest);
}

char	*expand_quotes(char *dest, char **src, t_shell *shell)
{
	char	quote;

	quote = **src;
	(*src)++;
	while (**src != quote)
	{
		if (**src == '$' && quote == '"')
			dest = expand_variable(dest, src, shell);
		else if (quote == '"')
			dest = add_chunk(dest, src, "$\"");
		else
			dest = add_chunk(dest, src, &quote);
		if (!dest)
			return (NULL);
	}
	(*src)++;
	return (dest);
}
