#include <readline/readline.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

static char	check_incomplete_line(char *input)
{
	char	open;

	open = '\0';
	while (*input)
	{
		if (open == '\0' && is_quote(*input))
			open = *input;
		else if (open == *input)
			open = '\0';
		input++;
	}
	return (open);
}

static char	*join_with_newline(char *left, char *right)
{
	char	*new;
	size_t	size_left;
	size_t	size_right;

	size_left = ft_strlen(left);
	size_right = ft_strlen(right);
	new = malloc((size_left + size_right + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, left, size_left);
    new[size_left] = '\n';
    ft_memcpy(new + size_left + 1, right, size_right);
    new[size_left + size_right + 1] = '\0';
	return (new);
}


char	*multiline_input(char *input)
{
	char	open;
	char	*line;
	char	*tmp;

	open = check_incomplete_line(input);
	if (open)
	{
		while (true)
		{
			line = readline("> ");
			if (!line)
				break ;
			tmp = input;
			input = join_with_newline(input, line);
			free(tmp);
			tmp = ft_strchr(line, open);
			free(line);
			if (tmp)
				break ;
		}
	}
	return (input);
}
