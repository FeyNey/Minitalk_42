/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 10:14:08 by acoste            #+#    #+#             */
/*   Updated: 2023/12/02 20:08:18 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>

int	longlong_putnbr_base(unsigned long long nb, char *base, int j);
int	unsigned_putnbr_base(unsigned int nb, char *base);
int	ft_carrefour(char str, va_list list);
int	putnbr_base(long nb, char *base);
int	ft_printf(const char *str, ...);
int	ft_putstr(char *str);
int	ft_putchar(char c);

#endif
