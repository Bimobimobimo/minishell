/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 00:44:27 by amonfret          #+#    #+#             */
/*   Updated: 2024/10/16 01:43:51 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr_big;
	char	*ptr_little;

	ptr_big = (char *)big;
	ptr_little = (char *)little;
	i = 0;
	if (ptr_little[0] == '\0')
		return (ptr_big);
	while (ptr_big[i] && i < len)
	{
		j = 0;
		while (ptr_big[i + j] && (i + j) < len
			&& ptr_big[i + j] == ptr_little[j] && ptr_little[j] != '\0')
		{
			j++;
		}
		if (ptr_little[j] == '\0')
			return (&ptr_big[i]);
		i++;
	}
	return (NULL);
}
