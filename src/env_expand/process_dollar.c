/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:59:27 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/13 10:59:27 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quotes(const char *token, size_t *i)
{
	if (token[(*i) + 1] == '"' || token[(*i) + 1] == '\'')
	{
		(*i)++;
		if (token[*i + 1] == '"')
			(*i) += 2;
		return (1);
	}
	return (0);
}

char	*dollar_unquoted(t_data *data, const char *token, size_t *i,
	t_env *env)
{
	int		var_start;
	char	*key;
	char	*value;

	value = NULL;
	if (skip_quotes(token, i))
		return (ft_strdup(""));
	var_start = ++(*i);
	if (!ft_isalnum(token[*i]) && token[*i] != '_' && token[*i] != '?')
		return (ft_strdup("$"));
	if (token[*i] == '?')
	{
		value = ft_itoa(data->exit_status);
		(*i)++;
	}
	else
	{
		while (ft_isalnum(token[*i]) || token[*i] == '_')
			(*i)++;
		key = ft_strndup(&token[var_start], *i - var_start);
		value = get_env_value(env, key);
		free(key);
	}
	return (value);
}

void	process_dollar(const char *token, t_vars *vars, t_env *env, size_t *i)
{
	vars->tmp = ft_strndup(&token[vars->start], *i - vars->start);
	vars->result = ft_append(vars->result, vars->tmp);
	free(vars->tmp);
	vars->var_start = ++(*i);
	if (!ft_isalnum(token[*i]) && token[*i] != '_' && token[*i] != '?')
		return ;
	if (token[*i] == '?')
	{
		vars->value = ft_itoa(vars->exit_status);
		(*i)++;
	}
	else
	{
		while (ft_isalnum(token[*i]) || token[*i] == '_')
			++(*i);
		vars->key = ft_strndup(&token[vars->var_start], *i - vars->var_start);
		vars->value = get_env_value(env, vars->key);
		free(vars->key);
	}
	if (vars->value)
	{
		vars->result = ft_append(vars->result, vars->value);
		free(vars->value);
	}
	vars->start = *i;
}
