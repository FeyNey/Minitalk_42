/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoste <acoste@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:39:18 by acoste            #+#    #+#             */
/*   Updated: 2024/07/05 10:20:38 by acoste           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "ft_printf/ft_printf.h"

char	*ft_memcpy(char *new_buffer, char *buffer, int len);
void	ft_errorhandle(int c);
void	send_bit(int pid, char c, int index);
void	signal_handler1(int sig);
void	signal_handler2(int sig);
void	send_message(int pid, char *str);
void	ft_buffer(char **buffer, char c, int *len);
void	ft_rcv_msg(char **buffer, int *msglen);
void	ft_handler(int sig, siginfo_t *info, void *context);
void	config_signals(void);
int		ft_checkargs(int argc);
int		ft_atoi(char *str);

#endif
