#include <stdlib.h>

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*byte_ptr;
	size_t			i;

	byte_ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		byte_ptr[i] = 0;
		i++;
	}
	return (s);
}
