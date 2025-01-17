/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehosaf <sehosaf@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:11:12 by sehosaf           #+#    #+#             */
/*   Updated: 2025/01/09 19:40:50 by sehosaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_signal_received = 0;

/*
	The client sends a message to the server by sending signals. The message is
	sent character by character converted to binary using SIGUSR1 and SIGUSR2.

	Then client receives a confirmation signal from the server.
*/

int	main(int argc, char *argv[])
{
	pid_t	pid;
	char	*message;

	if (argc != 3)
	{
		ft_printf("%sUsage: %s <PID> <MESSAGE>%s\n", RED, argv[0], END);
		exit(1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("%sInvalid PID%s\n", RED, END);
		exit(1);
	}
	signal(SIGUSR1, confirm_signal);
	message = argv[2];
	while (*message)
		send_message(pid, *message++);
	send_message(pid, '\0');
	return (0);
}
/*
	The confirm_signal function confirms that the message was sent successfully.
	If the signal is SIGUSR1, print a message indicating that the message
	was sent successfully.
*/

void	confirm_signal(int sig)
{
	extern volatile sig_atomic_t	g_signal_received;

	if (sig == SIGUSR1)
		g_signal_received = 1;
}

/*
	The message should be sent bit by bit. The client sends a message to the
	server by sending signals. The message is sent character by character
	converted to binary using SIGUSR1 and SIGUSR2.

	-	While the bit is less than 8, send a signal to the server.

		Takes the number 1 (0x01) and shifts it left by the bit.
		For example: 0x01 << 0 = 0x01, 0x01 << 1 = 0x02, 0x01 << 2 = 0x04, etc.
		Then & operator is used to check if the bit is set in the message.

		If the bit is set in the message, send SIGUSR1.
		Otherwise, send SIGUSR2.
*/

static void	print_error(void)
{
	ft_printf("%sError: Server not responding%s\n", RED, END);
	exit(1);
}

void	send_message(pid_t pid, char msg)
{
	int	bit;
	int	timeout;

	bit = 0;
	while (bit < 8)
	{
		g_signal_received = 0;
		if (msg & (0x01 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		timeout = 0;
		while (!g_signal_received && timeout < 50)
		{
			usleep(10);
			timeout++;
		}
		if (!g_signal_received)
			print_error();
		bit++;
	}
}

/*
	The ft_atoi is needed to convert the string representation of the process ID
	to an integer.
*/
int	ft_atoi(const char *str)
{
	int	sign;
	int	output;

	sign = 1;
	output = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		output = output * 10 + (*str - '0');
		str++;
	}
	return (output * sign);
}
