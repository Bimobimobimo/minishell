/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:34:50 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/25 11:08:38 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_space(const char **input)
{
	while (**input && is_space(**input))
		(*input)++;
}

void	append_string(char **token, const char *start, size_t len)
{
	char	*segment;
	char	*new_token;

	segment = ft_strndup(start, len);
	new_token = ft_strjoin(*token, segment);
	free(segment);
	free(*token);
	*token = new_token;
}

void	terminate_tokens(char **tokens, int count)
{
	if (tokens)
		tokens[count] = NULL;
}

int	is_separator(char c)
{
	if (c == ' ' || c == '\0')
		return (1);
	return (0);
}
