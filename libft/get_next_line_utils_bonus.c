/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:01:47 by amonfret          #+#    #+#             */
/*   Updated: 2025/01/02 09:45:39 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen2(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy2(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen2(src);
	if (size == 0)
		return (src_len);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

void	*free_mem(char **remainder, char **buffer)
{
	if (remainder && *remainder)
	{
		free(*remainder);
		*remainder = NULL;
	}
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	size_t	i;
// 	size_t	j;

// 	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		str[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 	{
// 		str[i + j] = s2[j];
// 		j++;
// 	}
// 	str[i + j] = '\0';
// 	return (str);
// }

// char	*ft_strdup(const char *s)
// {
// 	char	*ptr;
// 	char	*ptrdup;
// 	size_t	i;
// 	size_t	len;

// 	i = 0;
// 	len = ft_strlen(s);
// 	ptrdup = (char *)malloc((len + 1) * sizeof(char));
// 	if (!ptrdup)
// 		return (NULL);
// 	ptr = (char *)s;
// 	while (ptr[i])
// 	{
// 		ptrdup[i] = ptr[i];
// 		i++;
// 	}
// 	ptrdup[i] = '\0';
// 	return (ptrdup);
// }

// size_t	ft_strlcat(char *dst, const char *src, size_t size)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	dest_len;
// 	size_t	src_len;

// 	dest_len = 0;
// 	src_len = 0;
// 	while (dst[dest_len] && dest_len < size)
// 		dest_len++;
// 	while (src[src_len])
// 		src_len++;
// 	if (size == 0)
// 		return (src_len);
// 	i = dest_len;
// 	j = 0;
// 	if (size > dest_len + 1)
// 	{
// 		while (src[j] && i < size - 1)
// 		{
// 			dst[i++] = src[j++];
// 		}
// 		dst[i] = '\0';
// 	}
// 	return (dest_len + src_len);
// }
