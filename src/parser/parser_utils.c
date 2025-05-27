#include "minishell.h"


char	*trim_spaces(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

char	*get_word(char	**str)
{
	int	size;
	int	i;
	char	*word;

	size = 0;
	i = 0;
	while ((*str)[size] && (*str)[size] != ' ')
		size++;
	word = (char *)malloc(sizeof(char) * (size + 1));
	while(i < size)
	{
		word[i] = **str;
		i++;
		(*str)++;
	}
	word[i] = '\0';
	return (word);
}
