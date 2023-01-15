/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:55:41 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/15 16:50:56 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void handle_ack(int signum) {
    printf("ACK received\n");
}

int	signal_error(void)
{
	ft_printf("Error while handling signals...\n");
	return (0);
}

int	send_char(pid_t pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c & (1 << i))
			if (!(kill(pid, SIGUSR1)))
				return (signal_error());
		else
			if (!(kill(pid, SIGUSR2)))
				return (signal_error());
		usleep(100);
		i--;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	pid_t	target_pid;

	if (ac == 3)
	{
		i = 0;
		target_pid = ft_atoi(av[1]);
		signal(SIGUSR1, handle_ack);
		while (av[2][i])
		{
			if (!send_char(target_pid, av[2][i]))
				return (-1);
			i++;
		}
		if (!send_char(target_pid, '\0'))
			return (-1);
	}
	else
		ft_printf("Error with number of arguments.\n");
	return (0);
}
