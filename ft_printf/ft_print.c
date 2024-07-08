/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 20:52:07 by acoste            #+#    #+#             */
/*   Updated: 2023/12/02 20:52:17 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	if (str == NULL)
		return (write(1, "(null)", 6));
	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	putnbr_base(long nb, char *base)
{
	int	i;
	int	value;

	value = 0;
	i = 0;
	while (base[i])
		i++;
	if (nb < 0)
	{
		write(1, "-", 1);
		value++;
		nb = nb * -1;
	}
	if (nb >= i)
	{
		value += putnbr_base(nb / i, base);
		value += ft_putchar(base[nb % i]);
	}
	else
	{
		value += ft_putchar(base[nb % i]);
	}
	return (value);
}

int	unsigned_putnbr_base(unsigned int nb, char *base)
{
	unsigned int	i;
	int				value;

	value = 0;
	i = 0;
	while (base[i])
		i++;
	if (nb >= i)
	{
		value += putnbr_base(nb / i, base);
		value += ft_putchar(base[nb % i]);
	}
	else
	{
		value += ft_putchar(base[nb % i]);
	}
	return (value);
}

int	longlong_putnbr_base(unsigned long long nb, char *base, int j)
{
	unsigned long long	i;
	int					value;

	if (nb == 0)
		return (write(1, "(nil)", 5));
	value = 0;
	i = 0;
	if (j == 0)
		value += ft_putstr("0x");
	while (base[i])
		i++;
	if (nb >= i)
	{
		value += longlong_putnbr_base(nb / i, base, 1);
		value += ft_putchar(base[nb % i]);
	}
	else
		value += ft_putchar(base[nb % i]);
	return (value);
}
