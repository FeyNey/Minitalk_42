/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:26:40 by acoste            #+#    #+#             */
/*   Updated: 2024/07/04 20:25:06 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_sw = 0;

void	send_bit(int pid, char c, int index)
{
	int	bit;
	int	signal;

	bit = (c >> (7 - index)) & 1;
	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
		ft_errorhandle(8);
}
//send les bytes de gauches a droite

void	signal_handler1(int sig)
{
	(void)sig;
	g_sw = 1;
}
// le serveur envoie un signal SIGUSER1, on l'interprete;
//comme s'il disais j'ai recu un bit;

void	signal_handler2(int sig)
{
	(void)sig;
	write(1, "Message received\n", 18);
	exit(EXIT_SUCCESS);
}

// le serveur envoie un signal SIGUSR2, on l'interprete;
// comme : Le message entier a ete recu;

void	send_message(int pid, char *str)
{
	int	i;
	int	index;

	i = 0;
	while (str[i])
	{
		index = 0;
		while (index < 8)
		{
			g_sw = 0;
			send_bit(pid, str[i], index);
			index++;
			while (g_sw == 0)
				pause();
		}
		i++;
	}
	index = -1;
	while (index++ < 8)
	{
		g_sw = 0;
		send_bit(pid, '\0', index);
		while (g_sw == 0)
			pause();
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	ft_checkargs(argc);
	pid = (pid_t)(ft_atoi(argv[1]));
	signal(SIGUSR1, signal_handler1);
	signal(SIGUSR2, signal_handler2);
	send_message(pid, argv[2]);
	return (0);
}
