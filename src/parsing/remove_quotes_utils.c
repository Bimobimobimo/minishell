/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:37:57 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/25 11:07:26 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rm_quotes_handle_single_quoted(char *string, size_t *i)
{
	char	*tmp;
	int		start;

	tmp = NULL;
	if (string[*i] + 1 == '\'')
	{
		(*i) += 2;
		return (tmp);
	}
	start = ++(*i);
	while (string[*i] && string[*i] != '\'')
		(*i)++;
	tmp = ft_strndup(&string[start], *i - start);
	if (string[*i] == '\'')
		(*i)++;
	return (tmp);
}

char	*rm_quotes_handle_double_quoted(char *string, size_t *i)
{
	char	*tmp;
	int		start;

	tmp = NULL;
	start = ++(*i);
	while (string[*i] && string[*i] != '"')
		(*i)++;
	if (*i - start > 0)
		tmp = ft_strndup(&string[start], *i - start);
	else
		tmp = ft_strdup("");
	if (string[*i] == '"')
		(*i)++;
	return (tmp);
}

char	*rm_quotes_handle_unquoted(char	*string, size_t *i)
{
	char	*tmp;
	int		start;
	char	quote;

	tmp = NULL;
	start = (*i)++;
	while (string[*i] && (string[*i] != '\'' && string[*i] != '"'))
	{
		if (string[*i] == '='
			&& (string[*i + 1] == '\'' || string[*i + 1] == '"'))
		{
			quote = string[*i] + 1;
			(*i) += 2;
			while (string[*i] && string[*i] != quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	if (*i - start > 0)
		tmp = ft_strndup(&string[start], *i - start);
	else
		tmp = ft_strdup("");
	return (tmp);
}
