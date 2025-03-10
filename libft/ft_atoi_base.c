/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:14:55 by amonfret          #+#    #+#             */
/*   Updated: 2025/01/14 12:17:50 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 'a');
	return (c);
}

static int	get_digit(char c, int baseN)
{
	int	max_digit;

	if (baseN <= 10)
		max_digit = baseN - 1 + '0';
	else
		max_digit = baseN - 10 - 1 + 'a';
	if (c <= max_digit && c >= '0' && c <= '9')
		return (c - '0');
	if (c <= max_digit && c >= 'a' && c <= 'z')
		return (c + 10 - 'a');
	else
		return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	result;
	int	sign;
	int	digit;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	if (str == NULL || str_base < 2 || str_base > 16)
		return (0);
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i])
	{
		digit = get_digit(to_lower(str[i]), str_base);
		if (digit == -1)
			break ;
		result = result * str_base + digit;
		i++;
	}
	return (result * sign);
}
