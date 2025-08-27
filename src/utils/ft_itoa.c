#include <stdlib.h>
#include "utils.h"

static char	*zero_case(void)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static int	get_size(int n)
{
	int	size;

	size = 0;
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	while (n != 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

static char	*min_case(void)
{
	char	*str;

	str = malloc(12 * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, "-2147483648", 12);
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;

	if (n == 0)
		return (zero_case());
	if (n == -2147483648)
		return (min_case());
	size = get_size(n);
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	while (n != 0)
	{
		str[size - 1] = (n % 10) + 48;
		n /= 10;
		size--;
	}
	return (str);
}
