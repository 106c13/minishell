#include <stdio.h>
#include "utils.h"

char	*ft_nstrjoin(char **arr)
{
	int		size;
	size_t	i;
	char	**tmp;
	char	*str;

	size = 0;
	tmp = arr;
	while (*tmp)
	{
		size += ft_strlen(*tmp);
		tmp++;
	}
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	i = 0;
	while (*arr)
	{
		i += ft_strcpy(&str[i], *arr);
		arr++;
	}
	return (str);
}



char	*ft_strjoin(char *s1, char *s2)
{
	int		size;
	char	*str;

	if (!s2)
		return (s1);
	size = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[size] = '\0';
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy((str + ft_strlen(s1)), s2, ft_strlen(s2));
	return (str);
}

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	int		size;
	char	*str;

	if (!s1 || !s2)
		return (ft_strdup(s1));
	size = 0;
	size = ft_strlen(s1) + n;
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	ft_memcpy(str, s1, ft_strlen(s1));
	ft_memcpy((str + ft_strlen(s1)), s2, n);
	return (str);
}
