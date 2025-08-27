#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

char	**split_command(char *input)
{
	char	**parts;
	int		size;
	int		i;

	size = count_parts(input);
	parts = malloc(sizeof(char *) * (size + 1));
	if (!parts)
		return (NULL);
	i = 0;
	while (*input)
	{
		if (is_whitespace(*input))
			skip_spaces(&input);
		else
			parts[i++] = get_part(&input);
		if (!parts[i - 1])
		{
			free_parts(parts, i);
			return (NULL);
		}
	}
	parts[size] = NULL;
	return (parts);
}
