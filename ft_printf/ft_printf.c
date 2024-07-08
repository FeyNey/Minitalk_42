/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:55:29 by acoste            #+#    #+#             */
/*   Updated: 2023/12/02 20:06:57 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_carrefour(char s, va_list list)
{
	int	value;

	value = 0;
	if (s == 'c')
		value += ft_putchar((char)va_arg(list, int));
	else if (s == 's')
		value += ft_putstr((char *)va_arg(list, int *));
	else if (s == 'p')
		value += longlong_putnbr_base(va_arg(list, unsigned long long),
				"0123456789abcdef", 0);
	else if (s == 'd')
		value += putnbr_base(va_arg(list, int), "0123456789");
	else if (s == 'i')
		value += putnbr_base(va_arg(list, int), "0123456789");
	else if (s == 'u')
		value += unsigned_putnbr_base(va_arg(list, int), "0123456789");
	else if (s == 'x')
		value += unsigned_putnbr_base(va_arg(list, int), "0123456789abcdef");
	else if (s == 'X')
		value += unsigned_putnbr_base(va_arg(list, int), "0123456789ABCDEF");
	else if (s == '%')
		value += ft_putchar('%');
	return (value);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		value;
	int		i;

	i = 0;
	value = 0;
	va_start(list, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			value += ft_carrefour(str[i + 1], list);
			i = i + 2;
		}
		else
		{
			value += ft_putchar(str[i]);
			i++;
		}
	}
	va_end(list);
	return (value);
}
