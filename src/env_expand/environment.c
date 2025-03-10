/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:54:54 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/25 13:20:08 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

void	set_env_value(t_env **env, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			replace_value(current, value);
			return ;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	if (value)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL;
	new_node->next = *env;
	*env = new_node;
}

void	unset_env_value(t_env **env, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static char	*env_to_array_helper(char **array, t_env **cur, int i)
{
	char	*new_string;

	new_string = malloc(ft_strlen((*cur)->key)
			+ ft_strlen((*cur)->value) + 2);
	if (!new_string)
	{
		while (i--)
			free(array[i]);
		free(array);
		return (NULL);
	}
	ft_strlcpy(new_string, (*cur)->key, ft_strlen((*cur)->key) + 1);
	ft_strlcat(new_string, "=", ft_strlen((*cur)->key) + 2);
	if ((*cur)->value)
	{
		ft_strlcpy(new_string + ft_strlen(new_string), (*cur)->value,
			ft_strlen((*cur)->value) + 2);
	}
	(*cur) = (*cur)->next;
	return (new_string);
}

char	**env_to_array(t_env *env)
{
	char	**array;
	t_env	*current;
	int		i;

	i = env_array_malloc_size(env);
	array = malloc(sizeof(char *) * (i + 1));
	if (!array)
		return (NULL);
	i = 0;
	current = env;
	while (current)
	{
		array[i] = env_to_array_helper(array, &current, i);
		if (!array[i])
			return (NULL);
		i++;
	}
	array[i] = NULL;
	return (array);
}
