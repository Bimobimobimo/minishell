/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:32:27 by amonfret          #+#    #+#             */
/*   Updated: 2025/02/25 13:26:01 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*ptr;
	char	*ptrdup;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	ptrdup = (char *)malloc((len + 1) * sizeof(char));
	if (!ptrdup)
		return (NULL);
	ptr = (char *)s;
	while (ptr[i] && i < n)
	{
		ptrdup[i] = ptr[i];
		i++;
	}
	ptrdup[i] = '\0';
	return (ptrdup);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1[i] || !s2[i])
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

bool	key_syntax(char *key)
{
	int	i;

	i = 0;
	if ((key[0] >= '0' && key[0] <= '9') || key[0] == '\0' || key[0] == '=')
		return (false);
	while (key[i] && key[i] != '=')
	{
		if (key[i] != '_' && !ft_isalnum(key[i]))
			return (false);
		i++;
	}
	return (true);
}
