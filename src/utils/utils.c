/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azolotar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 18:11:07 by azolotar          #+#    #+#             */
/*   Updated: 2025/06/13 18:15:07 by azolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	size;

	size = 0;
	while (str[size])
	{
		size++;
	}
	return (size);
}

/* work on this func */
char	*get_shell_prompt(t_shell *shell)
{
	char	*shell_prompt;
	char	*path;
	char	*base;
	int		size;

	base = "minishell:";
	path = get_env_val(shell->env_list, "PWD");
	size = 0;
	size = ft_strlen(base) + ft_strlen(path);
	shell_prompt = malloc((size + 3) * sizeof(char));
	if (shell_prompt == NULL)
		return (NULL);
	shell_prompt[size] = '>';
	shell_prompt[size + 1] = ' ';
	shell_prompt[size + 2] = '\0';
	ft_memcpy(shell_prompt, base, ft_strlen(base));
	ft_memcpy((shell_prompt + ft_strlen(base)), path, ft_strlen(path));
	return (shell_prompt);
}

int	get_args_count(char **args)
{
	int	count;

	if (args == NULL)
		return (0);
	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	str_contains(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	if (s[i] == (char)c)
	{
		return ((char *)s + i);
	}
	return (0);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	s_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (s_len - start < len)
		len = s_len - start;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	digits_only(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	if (len == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	strlen_till(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	*str_append_char_safe(char *str, char c)
{
	char	*new;
	int		len;

	len = ft_strlen(str);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	ft_memcpy(new, str, len);
	new[len] = c;
	new[len + 1] = '\0';
	free(str);
	return (new);
}
