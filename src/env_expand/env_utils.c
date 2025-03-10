/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:41:38 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/07 15:17:45 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_env_node(t_env *head, t_env *new_node)
{
	while (head->next)
		head = head->next;
	head->next = new_node;
}

static void	swap_nodes(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = a->key;
	if (a->value)
		tmp_value = a->value;
	else
		tmp_value = NULL;
	a->key = b->key;
	if (b->value)
		a->value = b->value;
	else
		a->value = NULL;
	b->key = tmp_key;
	b->value = tmp_value;
}

static t_env	*env_malloc_error(t_env *new_node, t_env *copy)
{
	free_env_node(new_node);
	free_env_list(&copy);
	return (NULL);
}

static t_env	*duplicate_env_list(t_env *original)
{
	t_env	*copy;
	t_env	*new_node;
	t_env	*current;

	copy = NULL;
	current = original;
	while (current)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (env_malloc_error(new_node, copy));
		new_node->key = ft_strdup(current->key);
		new_node->value = NULL;
		if (current->value)
			new_node->value = ft_strdup(current->value);
		new_node->next = NULL;
		if (!copy)
			copy = new_node;
		else
			append_env_node(copy, new_node);
		current = current->next;
	}
	return (copy);
}

t_env	*create_sorted_copy(t_env *original)
{
	t_env	*copy;
	t_env	*current;
	int		swapped;

	copy = duplicate_env_list(original);
	if (!copy)
		return (NULL);
	current = copy;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		while (current && current->next)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				swap_nodes(current, current->next);
				swapped = 1;
			}
			current = current->next;
		}
		current = copy;
	}
	return (copy);
}
