/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:29:19 by amonfret          #+#    #+#             */
/*   Updated: 2024/10/31 18:12:16 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, int *count)
{
	write(1, &c, 1);
	(*count)++;
}

void	ft_putstr(char *s, int *count)
{
	if (s)
	{
		while (*s)
		{
			ft_putchar(*s++, count);
		}
	}
}

void	ft_putnbr(int n, int *count)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648", count);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-', count);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10, count);
	}
	ft_putchar(n % 10 + '0', count);
}

void	ft_putnbr_base(unsigned long nbr, char *base, int *count)
{
	if ((size_t)nbr > ft_strlen(base) - 1)
	{
		ft_putnbr_base(nbr / ft_strlen(base), base, count);
	}
	ft_putchar(base[nbr % ft_strlen(base)], count);
}

void	ft_ptrvoid_wrapper(void *p, char *base, int *count)
{
	if (!p)
		ft_putstr("(nil)", count);
	else
	{
		ft_putstr("0x", count);
		ft_putnbr_base((unsigned long)p, base, count);
	}
}
