/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 06:51:48 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/24 15:52:59 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

static int	is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static size_t	word_counter(const char *s, char sep)
{
	size_t	i;
	size_t	word_count;

	word_count = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] && is_sep(s[i], sep))
			i++;
		if (s[i] && !is_sep(s[i], sep))
			word_count++;
		while (s[i] && !is_sep(s[i], sep))
			i++;
	}
	return (word_count);
}

static char	*modified_strdup(const char *s, char sep)
{
	size_t	i;
	char	*word;

	i = 0;
	while (s[i] && !is_sep(s[i], sep))
		i++;
	word = (char *)malloc((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && !is_sep(s[i], sep))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	word_count;
	size_t	i;

	word_count = word_counter(s, c);
	i = 0;
	split = (char **)malloc((word_count + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (*s)
	{
		while (*s && is_sep(*s, c))
			s++;
		if (*s)
		{
			split[i] = modified_strdup(s, c);
			i++;
		}
		while (*s && !is_sep(*s, c))
			s++;
	}
	split[i] = NULL;
	return (split);
}
