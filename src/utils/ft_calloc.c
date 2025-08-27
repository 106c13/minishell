#include <stdlib.h>
#include <stdint.h>
#include "utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	l;

	if (size == 0 || count == 0)
	{
		ptr = malloc(1);
		ft_bzero(ptr, 1);
		return (ptr);
	}
	if (size == SIZE_MAX / count)
		return (NULL);
	l = size * count;
	ptr = malloc(l);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, l);
	return (ptr);
}
