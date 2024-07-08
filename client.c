/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:26:40 by acoste            #+#    #+#             */
/*   Updated: 2024/07/07 21:41:42 by acoste           ###   ########.fr       */
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
/*
	send les bytes de gauches a droite -> fonction kill, avec le pid du serveur
	de le code du bit correspondant au characteres (binaire)
	SIGUSR1 = 1, SIGUSR2 = 0
*/

void	signal_handler1(int sig)
{
	(void)sig;
	g_sw = 1;
}

/*
 le serveur envoie un signal SIGUSER1, on l'interprete;
comme s'il disais j'ai recu un bit;
*/

void	signal_handler2(int sig)
{
	(void)sig;
	write(1, "Message received\n", 18);
	exit(EXIT_SUCCESS);
}

/*
 le serveur envoie un signal SIGUSR2, on l'interprete;
 comme : Le message entier a ete recu;
*/

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

/*
	envoie du message bit par bit avec la fonction send bit,
	attente de la reception d'un signal de retour SIGUSR1 de la part du serveur
	signifiant qu'il a bien recu le bit et que l'on peut envoyer la suite
	permet la syncronisation serveur / client
*/


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

/*
	check des arguments, traitement du pid (char -> int via atoi)
	definission du comportement des signaux SIGUSR1 et SIGUSR2 en reception
	Envoie du message argv[2]
*/
