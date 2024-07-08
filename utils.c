/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 19:48:13 by acoste            #+#    #+#             */
/*   Updated: 2024/07/07 21:03:53 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	*ft_memcpy(char *new_buffer, char *buffer, int len)
{
	int	i;

	i = 0;
	if (!new_buffer && !buffer)
		return (NULL);
	while (i < len)
	{
		new_buffer[i] = buffer[i];
		i++;
	}
	return (new_buffer);
}

/*
	Copie de l'ancien buffer dans le nouveau
*/

void	ft_errorhandle(int c)
{
	if (c == 1)
		write(1, "Don't forget the ip serveur and to send a message\n", 51);
	else if (c == 2)
		write(1, "What do you wan't to transmit?\n", 32);
	else if (c == 3)
		write(1, "Too many arguments", 19);
	else if (c == 4)
		write(1, "invalid PID", 12);
	else if (c == 6)
		write(1, "Failed memory allocation\n", 26);
	else if (c == 7)
		write(1, "Failed handeling SIGUSR1\n", 26);
	else if (c == 9)
		write(1, "Failed handeling SIGUSR2\n", 26);
	else if (c == 8)
		write(1, "Failed sending signal\n", 23);
	exit(EXIT_FAILURE);
}
/*
	Gestion des erreurs via un code c donné en argument
*/

int	ft_checkargs(int argc)
{
	if (argc == 1)
		ft_errorhandle(1);
	if (argc == 2)
		ft_errorhandle(2);
	if (argc > 3)
		ft_errorhandle(3);
	return (0);
}

/*
	Verification des arguments passé en parametre
*/

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	if ((str[i] >= '\t' && str[i] <= '\r') || (str[i] == ' '))
		ft_errorhandle(4);
	if (str[i] == '-' || str[i] == '+')
		ft_errorhandle(4);
	if ((str[i] >= 'A' || str[i] <= 'Z') && (str[i] >= 'a' && str[i] <= 'z'))
		ft_errorhandle(4);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
/*
	Conversion char en int du PID
	et verif des caracteres
*/
