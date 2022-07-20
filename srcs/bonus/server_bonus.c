/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 19:31:10 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/20 17:29:48 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

t_server_data	g_data;

static void	set_sa_handler(void (*handler)(int, siginfo_t *, void *))
{
	g_data.action.sa_sigaction = handler;
	sigaction(SIGUSR1, &g_data.action, NULL);
	sigaction(SIGUSR2, &g_data.action, NULL);
}

static void	print_message(int *len)
{
	g_data.msg[*len] = '\0';
	ft_putstr_fd(g_data.msg, 1);
	*len = 0;
	g_data.len = 0;
	free(g_data.msg);
	g_data.msg = NULL;
	set_sa_handler(receive_message_length);
}

void	receive_message(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	i = 0;
	static int	len = 0;

	(void)context;
	c <<= 1;
	if (sig == SIGUSR2)
		c |= 1;
	i++;
	if (i == 8)
	{
		g_data.msg[len++] = c;
		c = 0;
		i = 0;
	}
	if (g_data.len == len)
		print_message(&len);
	usleep(50);
	kill(info->si_pid, sig);
}

void	receive_message_length(int sig, siginfo_t *info, void *context)
{
	static int	i = 0;

	(void)context;
	g_data.len <<= 1;
	if (sig == SIGUSR2)
		g_data.len |= 1;
	i++;
	if (i == 32)
	{
		i = 0;
		g_data.msg = ft_calloc((g_data.len + 1), sizeof(char));
		set_sa_handler(receive_message);
	}
	usleep(50);
	kill(info->si_pid, sig);
}

int	main(void)
{
	ft_printf("Server PID : %d\n", getpid());
	g_data.action.sa_flags = SA_SIGINFO;
	g_data.action.sa_sigaction = receive_message_length;
	sigemptyset(&g_data.action.sa_mask);
	sigaction(SIGUSR1, &g_data.action, NULL);
	sigaction(SIGUSR2, &g_data.action, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
