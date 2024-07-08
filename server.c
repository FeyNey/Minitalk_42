/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:26:32 by acoste            #+#    #+#             */
/*   Updated: 2024/07/07 21:41:43 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_buffer(char **buffer, char c, int *len)
{
	char	*new_buffer;

	new_buffer = malloc(*len + 2);
	if (!new_buffer)
		ft_errorhandle(6);
	if (ft_memcpy(new_buffer, *buffer, *len) == 0)
		ft_errorhandle(6);
	new_buffer[*len] = c;
	*len = *len + 1;
	new_buffer[*len] = '\0';
	free(*buffer);
	*buffer = new_buffer;
}
/*
	buffer stockant les caracteres arrivant au fur et a mesure
	en changeant de buffer a chaque fois pour augmenter la taille du msg
*/

void	ft_rcv_msg(char **buffer, int *msglen)
{
	ft_printf("%s\n", *buffer);
	free(*buffer);
	*buffer = NULL;
	*msglen = 0;
}
/*
	fonction message recu, affiche le message, free le buffer
	reinnitialisation des variables en cas de new message
*/

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	static int		bit_count = 0;
	static char		char_assambler = 0;
	static char		*buffer = NULL;
	static int		msg_len = 0;

	(void)context;
	if (sig == SIGUSR1)
		char_assambler |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8)
	{
		if (char_assambler != '\0')
			ft_buffer(&buffer, char_assambler, &msg_len);
		else
		{
			ft_rcv_msg(&buffer, &msg_len);
			kill(info->si_pid, SIGUSR2);
		}
		bit_count = 0;
		char_assambler = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

/*
	Fonction definissant le fonctionement de reception des signaux;
	SIGUSR1 -> 1	SIGUSR2 -> 0, envoi bit par bit de la part du client
	et stockage des 8 premiers dans le premier char ect...
	stockage des caracteres dans un buffer avant de les retransmettre (ftbuffer)
	si le caracteres '\0' est transmis, envoyer SIGUSR2
	il sera interpreter par le client comme message completed
	et remettre a 0 l'ensemble des variables en cas de new message
*/

void	config_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = ft_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	(void)sa.sa_restorer;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_errorhandle(7);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_errorhandle(9);
}

/*
	Mise en place de ma stucture sigaction et definition du comportement
	des signaux SIGUSR1 et SIGUSR2 dans ft_handler
	SA_SIGINFO permet de recup les infos du signal que l'on recoit
	-> pid du signal pour en revoyer
	sigemptyset initialise tout les signaux sigset_t a 0
	La fonction sigaction redirige les signaux passes
*/

int	main(int argc, char **argv)
{
	pid_t	pid;

	(void)argv;
	if (argc != 1)
	{
		write(1, "Wrong format, try : ./serveur\n", 31);
		return (0);
	}
	pid = getpid();
	ft_printf("Mon pid est : %d\n", pid);
	config_signals();
	while (1)
		pause();
	return (EXIT_SUCCESS);
}

/*
	Set up du serveur, recuperation du PID, boucle infinie attendant des signaux
	et configuration de la recuperation des signaux avec sigaction dans la
	fonction config_signals
*/
