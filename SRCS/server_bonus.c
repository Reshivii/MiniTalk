/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:02:50 by aburnott          #+#    #+#             */
/*   Updated: 2023/01/15 16:51:40 by aburnott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void send_ack(pid_t pid) {
    kill(pid, SIGUSR1);
}

void	signal_handler(int signum, siginfo_t *info)
{
	static char	buf[500];
	static int	buf_index = 0;
	static char	current_char = 0;
	static int	bits_received = 0;
	pid_t	sender_pid;

	current_char += (signum == SIGUSR1);
	bits_received++;
	if (bits_received == 8)
	{
		buf[buf_index] = current_char;
		buf_index++;
		if (current_char == '\0' || buf_index == 500)
		{
			write(1, buf, buf_index);
			buf_index = 0;
			sender_pid = info->si_pid;
			send_ack(sender_pid);
		}
		bits_received = 0;
		current_char = 0;
	}
	else
		current_char = current_char << 1;
}

int	main(void)
{
	pid_t	pid;
	struct sigaction sigusr1_action;

    sigusr1_action.sa_sigaction = signal_handler;
    sigusr1_action.sa_flags = SA_SIGINFO;
    sigemptyset(&sigusr1_action.sa_mask);
    sigaction(SIGUSR1, &sigusr1_action, NULL);
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	ft_printf("Waiting for message...\n");
	//signal(SIGUSR1, signal_handler);
	//signal(SIGUSR2, signal_handler);
	while (1)
		pause();
	return (0);
}
