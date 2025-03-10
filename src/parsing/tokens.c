/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:00:07 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/12 20:00:07 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_operator(const char **input, char ***tokens, int *count)
{
	char	op[3];

	ft_bzero(op, 3);
	op[0] = **input;
	(*input)++;
	if ((op[0] == '<' && **input == '<') || (op[0] == '>' && **input == '>'))
		op[1] = *(*input)++;
	*tokens = realloc_tokens(*tokens, *count);
	(*tokens)[(*count)++] = ft_strdup(op);
}

int	check_token_env_value(t_data *data, char *curr_token)
{
	size_t	i;
	char	*key;
	char	*value;

	if (!curr_token || curr_token[0] != '$' || (curr_token[0] == '$'
			&& curr_token[1] == '?') || curr_token[1] == '"'
		|| curr_token[1] == '\'')
		return (1);
	i = 1;
	while (curr_token[i] && ft_isalnum(curr_token[i]))
		i++;
	key = ft_strndup(curr_token + 1, i - 1);
	value = get_env_value(data->env, key);
	free(key);
	if (!value || ft_strlen(value) == 0)
	{
		if (value)
			free(value);
		return (0);
	}
	free(value);
	return (1);
}

char	**split_command(t_data *data, const char *input)
{
	char	**tokens;
	int		count;
	char	*current_token;

	tokens = NULL;
	count = 0;
	current_token = ft_strdup("");
	while (*input)
	{
		skip_space(&input);
		if (!*input)
			break ;
		if (ft_strchr("<>|", *input))
		{
			store_token(&tokens, &count, &current_token);
			handle_operator(&input, &tokens, &count);
		}
		else
		{
			handle_string(&input, &tokens, &current_token, &count);
			store_check(data, &tokens, &current_token, &count);
		}
	}
	terminate_tokens(tokens, count);
	return (free(current_token), tokens);
}
