/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:05:26 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/24 15:08:56 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	store_token(char ***tokens, int *count, char **cur)
{
	if (ft_strlen(*cur) > 0)
	{
		*tokens = realloc_tokens(*tokens, *count);
		(*tokens)[*count] = *cur;
		(*count)++;
		*cur = ft_strdup("");
	}
}

void	store_empty_token(char ***tokens, int *count, char **cur)
{
	if (*cur)
	{
		*tokens = realloc_tokens(*tokens, *count);
		(*tokens)[*count] = *cur;
		(*count)++;
		*cur = ft_strdup("");
	}
}
