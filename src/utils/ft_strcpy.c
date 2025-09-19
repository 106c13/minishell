#include <unistd.h>

size_t	ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (*src)
	{
		dest[i] = *src;
		i++;
		src++;
	}
	return (i);
}
