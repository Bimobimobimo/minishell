/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:40:08 by amonfret          #+#    #+#             */
/*   Updated: 2024/10/23 13:32:03 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	cmp_len(size_t len, size_t s_len, size_t start)
{
	if (start >= s_len)
		return (0);
	if (len > s_len - start)
		return (s_len - start);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_string;
	size_t	i;

	if (!s)
		return (NULL);
	if (len == 0 || start >= ft_strlen(s))
	{
		new_string = malloc(1);
		if (new_string)
			new_string[0] = '\0';
		return (new_string);
	}
	len = cmp_len(len, ft_strlen(s), start);
	i = 0;
	new_string = (char *)malloc((len + 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	while (i < len && ((char *)(s + start))[i] != '\0')
	{
		new_string[i] = ((char *)(s + start))[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}
