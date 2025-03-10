/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:56:02 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/24 15:19:03 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_empty_quotes(char quote, char **cur_token)
{
	if (quote == '\'')
		append_string(cur_token, "\'\'", 3);
	else if (quote == '"')
		append_string(cur_token, "\"\"", 3);
}

static void	handle_quoted(char ***tokens, const char **input,
	char **cur_token, int *count)
{
	char		quote;
	const char	*start;

	quote = **input;
	if (*(*input + 1) == quote && !is_separator(*(*input + 2)))
	{
		append_empty_quotes(quote, cur_token);
		(*input) += 2;
	}
	else if (*(*input + 1) == quote)
	{
		store_empty_token(tokens, count, cur_token);
		(*input) += 2;
	}
	else
	{
		start = (*input)++;
		while (**input && **input != quote)
			(*input)++;
		if (**input == quote)
		{
			(*input)++;
			append_string(cur_token, start, *input - start);
		}
	}
}

static void	handle_unquoted(const char **input, char **token)
{
	const char	*start;

	start = *input;
	while (**input && !is_space(**input) && **input != '\'' && **input != '"'
		&& !ft_strchr("<>|", **input))
		(*input)++;
	append_string(token, start, *input - start);
}

void	handle_string(const char **input, char ***tokens, char **cur_token,
	int *count)
{
	while (**input && !is_space(**input) && !ft_strchr("<>|", **input))
	{
		if (**input == '\'' || **input == '"')
			handle_quoted(tokens, input, cur_token, count);
		else
			handle_unquoted(input, cur_token);
	}
}

void	store_check(t_data *data, char ***tokens, char **curr_token, int *count)
{
	if (*curr_token[0] == '$' && ft_strlen(*curr_token) > 1
		&& ft_strcmp(*curr_token, "$?") != 0)
	{
		if (check_token_env_value(data, *curr_token))
			store_token(tokens, count, curr_token);
		else
		{
			free(*curr_token);
			*curr_token = ft_strdup("");
		}
	}
	else
		store_token(tokens, count, curr_token);
}
