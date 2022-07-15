/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeongki <hyeongki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:50:57 by hyeongki          #+#    #+#             */
/*   Updated: 2022/07/15 20:10:09 by hyeongki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include "../../ft_printf/libft/libft.h"
#include <unistd.h>

static void	receive_reply(int sig)
{
	if (sig == SIGUSR1)
		return ;
	else if (sig == SIGUSR2)
		ft_puterr("Signal send failed");
}

static void	send_message_length(pid_t pid, unsigned int len)
{
	int				i;
	unsigned int	tmp;

	i = 0;
	tmp = len;
	while (i++ < 32)
	{
		len <<= 1;
		if (len >= tmp)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
		tmp = len;
	}
}

static void	send_message(pid_t pid, char *str)
{
	int				i;
	int				j;
	unsigned char	c;
	unsigned char	tmp;

	i = 0;
	while (str[i])
	{
		j = 0;
		c = (unsigned char)str[i];
		tmp = c;
		while (j++ < 8)
		{
			c <<= 1;
			if (c >= tmp)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			pause();
			tmp = c;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;

	if (argc != 3)
		ft_puterr("Invalid number of factors.\n\
Usage: ./client [Server PID] [Message]");
	pid = (pid_t)ft_atoi(argv[1]);
	if (pid < 101 || pid > 99998)
		ft_puterr("Invalid PID");
	signal(SIGUSR1, receive_reply);
	signal(SIGUSR2, receive_reply);
	send_message_length(pid, ft_strlen(argv[2]));
	send_message(pid, argv[2]);
	return (0);
}
