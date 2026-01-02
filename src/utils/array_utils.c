#include <stdlib.h>
#include <stdio.h>
#include "utils.h"

char	**join_str_arrays(char **a1, char **a2)
{
	int		size1;
	int		size2;
	char	**new;

	size1 = 0;
	size2 = 0;
	while (a1 && a1[size1])
		size1++;
	while (a2 && a2[size2])
		size2++;
	new = malloc(sizeof(char *) * (size1 + size2 + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, a1, size1 * sizeof(char *));
	ft_memcpy(new + size1, a2, size2 * sizeof(char *));
	new[size1 + size2] = NULL;
	if (a2)
		free(a2);
	return (new);
}

char	**append_str_array(char **arr, char *tail)
{
	char	**new;
	int		size;

	size = 0;
	while (arr && arr[size])
		size++;
	new = malloc(sizeof(char *) * (size + 2));
	if (!new)
		return (NULL);
	ft_memcpy(new, arr, size * sizeof(char *));
	new[size] = tail;
	new[size + 1] = NULL;
	if (arr)
		free(arr);
	return (new);
}	
