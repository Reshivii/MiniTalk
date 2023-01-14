/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:55:41 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/14 19:24:27 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	char_to_bits(pid_t pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			if (kill(pid, SIGUSR1) == -1)
				return (0);
		else
			if (kill(pid, SIGUSR2) == -1)
				return (0);
		bit++;
		usleep(100);
	}
	return (1);
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		i;

	i = -1;
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		while (av[2][++i])
		{
			if (!char_to_bits(pid, av[2][i]))
			{
				ft_printf("Error with signals..");
				return (-1);
			}
		}
		if (!char_to_bits(pid, '\0'))
		{
			ft_printf("Error with signals..");
			return (-1);
		}
	}
	else
		ft_printf("Error. Missing pid and/or arguments.\n");
	return (0);
}
