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

int	get_operator_type(char *word)
{
	if (ft_strcmp(word, "&") == 0)
		return (1);
	if (ft_strcmp(word, "|") == 0)
		return (2);
	if (ft_strcmp(word, "&&") == 0)
		return (3);
	if (ft_strcmp(word, "||") == 0)
		return (4);
	return (0);
}
