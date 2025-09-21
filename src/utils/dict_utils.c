#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "utils.h"

char	*get_dict_val(t_dict *dict, char *key)
{
	if (!dict || !key)
		return (NULL);
	while (dict)
	{
		if (ft_strcmp(dict->key, key) == 0)
			return (ft_strdup(dict->val));
		dict = dict->next;
	}
	return (NULL);
}

static t_dict	*new_dict_node(char *key, char *val)
{
	t_dict	*new;

	new = ft_calloc(1, sizeof(t_dict));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (!new->key)
		return (free(new), NULL);
	if (val)
		new->val = ft_strdup(val);
	if (val && !new->val)
		return (free(new->key), free(new), NULL);
	return (new);
}

t_dict	*set_dict_val(t_dict *head, char *key, char *val)
{
	t_dict	*prev;
	t_dict	*node;

	if (!head)
		return (new_dict_node(key, val));
	node = head;
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
		{
			if (!val)
				node->val = NULL;
			else
				node->val = ft_strdup(val);
			return (head);
		}
		prev = node;
		node = node->next;
	}
	node = new_dict_node(key, val);
	if (prev)
		prev->next = node;
	return (head);
}

void	print_dict(t_dict *dict)
{
	while (dict)
	{
		if (dict->val == NULL)
			printf("%s\n", dict->key);
		else
			printf("%s='%s'\n", dict->key, dict->val);
		dict = dict->next;
	}
}
