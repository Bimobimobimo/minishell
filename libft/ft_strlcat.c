/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 05:23:35 by amonfret          #+#    #+#             */
/*   Updated: 2024/10/15 06:17:11 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	dest_len = 0;
	src_len = 0;
	while (dst[dest_len] && dest_len < size)
		dest_len++;
	while (src[src_len])
		src_len++;
	if (size == 0)
		return (src_len);
	i = dest_len;
	j = 0;
	if (size > dest_len + 1)
	{
		while (src[j] && i < size - 1)
		{
			dst[i++] = src[j++];
		}
		dst[i] = '\0';
	}
	return (dest_len + src_len);
}
