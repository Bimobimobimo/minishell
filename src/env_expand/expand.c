/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:20:48 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/25 11:10:58 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_append(char *dest, char *src)
{
	size_t	dest_len;
	size_t	src_len;
	char	*new;

	dest_len = 0;
	if (dest)
		dest_len = ft_strlen(dest);
	src_len = 0;
	if (src)
		src_len = ft_strlen(src);
	new = malloc(dest_len + src_len + 1);
	if (!new)
		return (NULL);
	if (dest)
		ft_strlcpy(new, dest, dest_len + 1);
	if (src)
		ft_strlcpy(new + dest_len, src, src_len + 1);
	if (dest)
		free(dest);
	return (new);
}

char	*expand_token(t_data *data, const char *token, t_env *env)
{
	size_t	i;
	char	*result;
	char	*tmp;

	result = NULL;
	tmp = NULL;
	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && (token[i + 1] == '"' || token[i + 1] == '\''))
			i++;
		if (token[i] == '\'')
			tmp = process_single(token, &i);
		else if (token[i] == '"')
			tmp = process_double(data, token, &i, env);
		else
			tmp = process_unquoted(data, token, &i, env);
		if (tmp)
		{
			result = ft_append(result, tmp);
			free(tmp);
		}
	}
	return (result);
}

char	**expand(t_data *data, char **tokens, t_env *env)
{
	char	*expanded;
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "<<", 2) == 0 && tokens[i + 1])
		{
			i += 2;
			continue ;
		}
		else
		{
			expanded = expand_token(data, tokens[i], env);
			if (expanded)
			{
				free(tokens[i]);
				tokens[i] = expanded;
			}
			i++;
		}
	}
	return (tokens);
}
