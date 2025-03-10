/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:19:59 by amonfret          #+#    #+#             */
/*   Updated: 2024/11/05 19:10:12 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

static void	check_char(char c, va_list *args, int *count)
{
	char	*next_string;

	if (c == 'c')
		ft_putchar((char)va_arg(*args, int), count);
	else if (c == 's')
	{
		next_string = va_arg(*args, char *);
		if (next_string)
			ft_putstr(next_string, count);
		else
			ft_putstr("(null)", count);
	}
	else if (c == 'p')
		ft_ptrvoid_wrapper(va_arg(*args, void *), "0123456789abcdef", count);
	else if (c == 'd' || c == 'i')
		ft_putnbr((int)va_arg(*args, int), count);
	else if (c == 'u')
		ft_putnbr_base(va_arg(*args, unsigned int), "0123456789", count);
	else if (c == 'x')
		ft_putnbr_base(va_arg(*args, unsigned int), "0123456789abcdef", count);
	else if (c == 'X')
		ft_putnbr_base(va_arg(*args, unsigned int), "0123456789ABCDEF", count);
	else if (c == '%')
		ft_putchar('%', count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1))
		{
			str++;
			check_char(*str, &args, &count);
		}
		else
			ft_putchar(*str, &count);
		str++;
	}
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	void *ptr = &ptr;
// 	int number = 123;

// 	printf("==== Testing ft_printf against standard printf ====\n\n");

// 	printf("Character and String Tests:\n");
// 	printf("Expected: Hello %c World\n", 'A');
// 	ft_printf("Actual  : Hello %c World\n", 'A');

// 	printf("Expected: This is a %s\n", "string");
// 	ft_printf("Actual  : This is a %s\n", "string");
// 	printf("\n");

// 	printf("Pointer Test:\n");
// 	printf("Expected: Pointer address: %p\n", ptr);
// 	ft_printf("Actual  : Pointer address: %p\n", ptr);
// 	printf("Expected: Pointer address: %p %p \n", NULL, NULL);
// 	ft_printf("Actual  : Pointer address: %p %p \n", NULL, NULL);
// 	printf("\n");

// 	printf("Integer Tests:\n");
// 	printf("Expected: Signed integer: %d\n", number);
// 	ft_printf("Actual  : Signed integer: %d\n", number);

// 	printf("Expected: Signed integer (i): %i\n", number);
// 	ft_printf("Actual  : Signed integer (i): %i\n", number);
// 	printf("\n");

// 	printf("Unsigned Integer Test:\n");
// 	printf("Expected: Unsigned integer: %u\n", (unsigned int)number);
// 	ft_printf("Actual  : Unsigned integer: %u\n", (unsigned int)number);
// 	printf("\n");

// 	printf("Hexadecimal Tests:\n");
// 	printf("Expected: Hex (lowercase): %x\n", number);
// 	ft_printf("Actual  : Hex (lowercase): %x\n", number);

// 	printf("Expected: Hex (uppercase): %X\n", number);
// 	ft_printf("Actual  : Hex (uppercase): %X\n", number);
// 	printf("\n");

// 	printf("Percent Symbol Test:\n");
// 	printf("Expected: Just a percent sign: %%\n");
// 	ft_printf("Actual  : Just a percent sign: %%\n");

// 	return (0);
// }
