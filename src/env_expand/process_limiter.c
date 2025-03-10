/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_limiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:51:40 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/19 09:57:57 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_chevron(const char *token, size_t *i)
{
	while (token[*i] && token[*i] == '<')
		(*i)++;
}

static void	skip_spaces(const char *token, size_t *i)
{
	while (token[*i]
		&& (token[*i] == ' ' || token[*i] == '\t' || token[*i] == '\n'))
		(*i)++;
}

static void	handle_limiter_quotes(const char *token, size_t *i)
{
	char	quote;

	quote = token[*i];
	(*i)++;
	while (token[*i] && token[*i] != quote)
		(*i)++;
	if (token[*i] == quote)
		(*i)++;
}

static void	handle_word(const char *token, size_t *i)
{
	while (token[*i]
		&& (token[*i] != ' ' || token[*i] != '\t' || token[*i] != '\n'))
		(*i)++;
}

char	*process_limiter(const char *token, size_t *i)
{
	char	*result;
	size_t	start;

	result = NULL;
	start = *i;
	skip_chevron(token, i);
	skip_spaces(token, i);
	if (token[*i] == '\'' || token[*i] == '"')
		handle_limiter_quotes(token, i);
	else
		handle_word(token, i);
	result = ft_strndup(&token[start], *i - start);
	return (result);
}
