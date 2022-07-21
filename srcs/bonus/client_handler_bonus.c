/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:46:17 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/21 19:04:56 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_bonus.h"
#include <signal.h>
#include "../../ft_printf/libft/libft.h"

extern int	g_signal;

void	receive_connection_reply(int sig)
{
	if (sig == SIGUSR1)
		return ;
	if (sig == SIGUSR2)
		ft_puterr(RED "Connection to server failed, \
The server might be connecting with another client\n");
}

void	receive_message_reply(int sig)
{
	if (sig != g_signal)
		ft_puterr(RED "Received wrong reply\n");
	g_signal = 0;
}
