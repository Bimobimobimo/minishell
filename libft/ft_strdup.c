/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 03:17:55 by amonfret          #+#    #+#             */
/*   Updated: 2024/10/16 03:38:04 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
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
	while (ptr[i])
	{
		ptrdup[i] = ptr[i];
		i++;
	}
	ptrdup[i] = '\0';
	return (ptrdup);
}
