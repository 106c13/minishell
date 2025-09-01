#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "utils.h"
#include "tokenizer.h"


t_token *build_token_array(char **parts)
{
	t_token	*tokens;
	int		size;
	int		i;

	size = split_size(parts);
	tokens = ft_calloc((size + 1), sizeof(t_token));
	if (!tokens)
		return (NULL);
	i = 0;
	while (parts[i])
	{
		set_token_type(&tokens[i], parts[i]);
		tokens[i].value = parts[i];
		printf("\033[38;5;34m[DEBUG] TYPE %d VALUE %s\033[0m\n", tokens[i].type, tokens[i].value);
		i++;
	}
	return (tokens);
}

t_token	*tokenize(char *input)
{
	char	**parts;
	t_token	*tokens;

	parts = split_command(input);
	if (!parts)
	{
		printf("Error during spliting\n");
		return (NULL);
	}
	tokens = build_token_array(parts);
	free(parts);
	if (!tokens)
	{
		printf("Error during tokenizing\n");
		return (NULL);
    }
	return (tokens);
}
