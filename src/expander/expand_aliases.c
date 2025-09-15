#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "minishell.h"
#include "tokenizer.h"
#include "utils.h"
#include "defines.h"

static t_token	*new_token_array(t_token *left, t_token *right)
{
	t_token	*dest;
	int		size;

	size = 0;
	size = get_t_array_size(left) + get_t_array_size(right);
	dest = malloc(sizeof(t_token) * (size + 1));
	if (!dest)
		return (free(left), free(right), NULL);
	dest[size].type = 0;
	return (dest);
}

static t_token	*join_tokens(t_token *left, char *src)
{
	t_token	*dest;
	t_token	*right;
	t_token	*tmp;
	int		i;

	right = tokenize(src);
	if (!right)
		return (left);
	dest = new_token_array(left, right);
	i = 0;
	tmp = left;
	while (tmp && tmp->type)
		ft_memcpy(&dest[i++], tmp++, sizeof(t_token));
	tmp = right;
	while (tmp->type)
		ft_memcpy(&dest[i++], tmp++, sizeof(t_token));
	free(left);
	free(right);
	return (dest);
}

t_token	*expand_aliases(t_token *old, t_dict *aliases)
{
	t_token	*new;
	t_token	*tmp;
	bool	is_first;

	if (!aliases)
		return (old);
	tmp = old;
	new = NULL;
	is_first = true;
	while (tmp->type)
	{
		if (tmp->type == WORD && is_first)
		{
			is_first = false;
			new = join_tokens(new, get_dict_val(aliases, tmp->value));
		}
		else if (t_is_operator(tmp->type))
			is_first = true;
		tmp++;
	}
	if (!new)
		return (old);
	return (new);
}
