/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:34:39 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/25 11:10:16 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env_list;
	t_env	*current;
	t_env	*new_node;

	env_list = NULL;
	while (*envp)
	{
		new_node = create_env_node(*envp);
		if (!env_list)
			env_list = new_node;
		else
			current->next = new_node;
		current = new_node;
		envp++;
	}
	return (env_list);
}

t_env	*create_env_node(const char *env_str)
{
	t_env	*new_node;
	char	*delimiter;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	delimiter = ft_strchr(env_str, '=');
	if (delimiter)
	{
		new_node->key = ft_strndup(env_str, delimiter - env_str);
		new_node->value = ft_strdup(delimiter + 1);
	}
	else
	{
		new_node->key = ft_strdup(env_str);
		new_node->value = NULL;
	}
	new_node->next = NULL;
	return (new_node);
}

void	free_env_node(t_env *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	free_env_list(t_env **list)
{
	t_env	*curr;
	t_env	*previous;

	curr = *list;
	while (curr)
	{
		previous = curr;
		curr = curr->next;
		if (previous)
			free_env_node(previous);
	}
	*list = NULL;
}

void	replace_value(t_env *env, const char *value)
{
	if (env->value)
		free(env->value);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
}
