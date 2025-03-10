/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arrays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 15:41:09 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/07 15:16:18 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	tab_lign_nb(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}

char	**realloc_tokens(char **tokens, int count)
{
	char	**new_tokens;
	int		i;

	i = 0;
	new_tokens = malloc(sizeof(char *) * (count + 2));
	if (!new_tokens)
		return (NULL);
	while (i < count + 2)
		new_tokens[i++] = NULL;
	if (tokens)
	{
		i = 0;
		while (tokens[i])
		{
			new_tokens[i] = tokens[i];
			i++;
		}
		free(tokens);
	}
	else
		i = 0;
	new_tokens[i] = NULL;
	return (new_tokens);
}

int	env_array_malloc_size(t_env *env)
{
	t_env	*current;
	int		i;

	current = env;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
