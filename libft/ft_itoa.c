/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 07:30:09 by amonfret          #+#    #+#             */
/*   Updated: 2024/10/17 08:47:32 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

static void	set_string_zero(char *s, int n)
{
	if (n == 0)
	{
		s[0] = '0';
	}
	if (n < 0)
	{
		s[0] = '-';
	}
}

static size_t	num_len(int n)
{
	size_t	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t			len;
	char			*string;
	unsigned int	num;

	len = num_len(n);
	string = (char *)malloc((len + 1) * sizeof(char));
	if (!string)
		return (NULL);
	string[len] = '\0';
	set_string_zero(string, n);
	if (n < 0)
		num = -n;
	else
		num = n;
	while (num != 0)
	{
		string[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (string);
}
