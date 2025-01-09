/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehosaf <sehosaf@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:49:42 by sehosaf           #+#    #+#             */
/*   Updated: 2025/01/09 19:50:26 by sehosaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
	The server receives the signals from the client and decodes them.
	The signals are received by the server in the handle_signal function.
	Listening to the signals SIGUSR1 and SIGUSR2. Which represent the binary
	values 0 and 1 respectively.

	When the server receives a signal, it decodes the signal and prints the
	character to the standard output. The server will continue to listen for
	signals until it does not receive any signals for 2 minutes.

	-	The signal mask is set to be empty. Meaning no signals are blocked.
		sa_mask specifies a mask of signals which should be blocked
		(i.e., added to the signal mask of the thread in which the signal
		handler	is invoked) during execution of the signal handler.
		sigemptyset — initialize and empty a signal set

	-	Set the flags to SA_SIGINFO means the signal handler takes three
		arguments as defined in the sigaction structure:
		"SA_SIGINFO: The signal handler takes three arguments, not one.
		In this case, sa_sigaction should be set instead of sa_handler."
*/

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	sigset_t			block_mask;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("%sUsage: %s%s\n", RED, argv[0], END);
		exit(1);
	}
	sigemptyset(&block_mask);
	sigaddset(&block_mask, SIGUSR1);
	sigaddset(&block_mask, SIGUSR2);
	sa.sa_sigaction = handle_signal;
	sa.sa_mask = block_mask;
	sa.sa_flags = SA_SIGINFO;
	ft_printf("%sThe server is ready [PID: %d]%s\n\v", CYAN, getpid(), END);
	while (argc == 1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}

/*
	The send_feedback function sends a SIGUSR1 signal to the client to confirm
	that the message has been received. If the signal is sent successfully,
	it will print sender's process ID. Otherwise, it will print an error message.
*/

static void	send_feedback(siginfo_t *info)
{
	int	return_value;
	int	pid;

	pid = info->si_pid;
	return_value = kill(pid, SIGUSR1);
	if (return_value == -1)
		ft_printf("%sError sending feedback to %d%s\n", RED, pid, END);
	else
		ft_printf("\n%sSender:%s %d\n\v", YELLOW, END, pid);
}

/*
	These three arguments are as follows

	sig    The number of the signal that caused invocation of the
			handler.

	info   A pointer to a siginfo_t, which is a structure containing
			further information about the signal, as described below.

	ucontext
			This is a pointer to a ucontext_t structure, cast to
			void *.  The structure pointed to by this field contains
			signal context information that was saved on the user-
			space stack by the kernel; for details, see sigreturn(2).
			Further information about the ucontext_t structure can be
			found in getcontext(3) and signal(7).  Commonly, the
			handler function doesn't make any use of the third
			argument.

	If the signal is SIGUSR1, it will set the 'bit'th bit of 'i' to 1.
	If the signal is SIGUSR2, it will set the 'bit'th bit of 'i' to 0.

	0x01 is 1 in binary (00000001). The expression (0x01 << bit_th) shifts
	the binary representation of 0x01 to the left by 'bit_th' places.
	This effectively creates a binary number where only the 'bit_th' bit
	is 1 and all other bits are 0. The |= operator then performs a bitwise
	OR operation between i and the result of the shift operation,
	and assigns the result back to i. This sets the 'bit_th' bit of i to 1,
	while leaving all other bits of i unchanged.

	When 'bit' reaches 8 (indicating that a full byte of data has been received),
	it will print the character represented by 'i' if it's not '\0'.

	If 'i' is '\0', it will print a newline character and send a SIGUSR2 signal
	to the client to confirm that the message has been received.
		si_pid - Sending process ID

	Finally, it will reset 'bit_th' and 'i' to 0 to receive the next byte of data
*/

static void	process_byte(t_buffer *buf, siginfo_t *info)
{
	if (*buf->i != '\0')
	{
		buf->data[buf->pos] = *buf->i;
		buf->pos++;
		if (buf->pos >= 1024)
		{
			write(STDOUT_FILENO, buf->data, buf->pos);
			buf->pos = 0;
		}
	}
	else
	{
		if (buf->pos > 0)
			write(STDOUT_FILENO, buf->data, buf->pos);
		buf->pos = 0;
		send_feedback(info);
	}
	*buf->bit_th = 0;
	*buf->i = 0;
}

void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	static t_buffer	buf;
	static int		bit_th;
	static int		i;

	(void)ucontext;
	if (buf.pid != info->si_pid)
	{
		if (buf.pos > 0)
			write(STDOUT_FILENO, buf.data, buf.pos);
		buf.pos = 0;
		bit_th = 0;
		i = 0;
		buf.pid = info->si_pid;
	}
	buf.i = &i;
	buf.bit_th = &bit_th;
	if (sig == SIGUSR1)
		i |= (0x01 << bit_th);
	bit_th++;
	kill(info->si_pid, SIGUSR1);
	if (bit_th == 8)
		process_byte(&buf, info);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
