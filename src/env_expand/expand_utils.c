/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:20:50 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/25 11:10:47 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_single(const char *token, size_t *i)
{
	char	*result;
	size_t	start;

	result = NULL;
	start = (*i)++;
	while (token[*i] && token[*i] != '\'')
		(*i)++;
	result = ft_strndup(&token[start], *i - start + 1);
	if (token[*i])
		(*i)++;
	return (result);
}

char	*process_double(t_data *data, const char *token, size_t *i, t_env *env)
{
	t_vars	vars;

	vars.exit_status = data->exit_status;
	vars.result = NULL;
	vars.value = NULL;
	vars.start = (*i)++;
	while (token[*i] && token[*i] != '"')
	{
		if (token[*i] == '$' && token[(*i) + 1] != '"'
			&& token[(*i) + 1] != '\'')
			process_dollar(token, &vars, env, i);
		else
			(*i)++;
	}
	vars.tmp = ft_strndup(&token[vars.start], *i - vars.start + 1);
	vars.result = ft_append(vars.result, vars.tmp);
	free(vars.tmp);
	if (token[*i] == '"')
		(*i)++;
	return (vars.result);
}

static bool	is_quote_dollar(char c)
{
	if (c == '\'' || c == '"' || c == '$')
		return (true);
	return (false);
}

char	*process_unquoted(t_data *data, const char *token, size_t *i,
	t_env *env)
{
	char	*result;
	char	*tmp;
	int		start;

	result = NULL;
	start = *i;
	while (token[*i] != '\0' && !is_quote_dollar(token[*i]))
		(*i)++;
	tmp = ft_strndup(&token[start], *i - start);
	if (!tmp)
		return (NULL);
	result = ft_append(result, tmp);
	free(tmp);
	if (token[*i] == '$')
	{
		tmp = dollar_unquoted(data, token, i, env);
		if (tmp)
		{
			result = ft_append(result, tmp);
			free(tmp);
		}
	}
	return (result);
}
