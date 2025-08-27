#include <stdio.h>
#include "utils.h"

int	count_parts(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (is_whitespace(*line))
			skip_spaces(&line);
		else 
		{
			skip_part(&line);
			count++;
		}
	}
	printf("\033[38;5;34m[DEBUG] PARTS COUNT: %d\033[0m\n", count);
	return (count);
}

char	*get_part(char **str)
{
	char	*part;
	int		size;

	size = skip_part(str);
	part = malloc(sizeof(char) * (size + 1));
	if (!part)
		return (NULL);
	part[size] = '\0';
	ft_memcpy(part, (*str - size), size);
	return (part);
}

void free_parts(char **parts, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(parts[i++]);
	free(parts);
}

int	split_size(char **parts)
{
	int	size;

	if (!parts)
		return (0);
	size = 0;
	while (parts[size])
		size++;
	return (size);
}
