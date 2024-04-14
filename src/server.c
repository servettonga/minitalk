/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehosaf <sehosaf@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 10:49:42 by sehosaf           #+#    #+#             */
/*   Updated: 2024/04/14 16:29:37 by sehosaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void handle_signal(int sig, siginfo_t *info, void *ucontext);

/*
	The server receives the signals from the client and decodes them.

	-	Fist check if the argument count is 1, if not print the usage message.

	-	Then print the server's PID.

	-	Next, set the signal handler to handle_signal.

	-	After that, set the signal mask to empty. Meaning no signals are blocked.
		sa_mask specifies a mask of signals which should be blocked
		(i.e., added to the signal mask of the thread in which the signal handler
		is invoked) during execution of the signal handler.
		sigemptyset — initialize and empty a signal set

	-	Then set the flags to SA_SIGINFO. Meaning the signal handler takes
		three arguments as defined in the sigaction structure:
		"SA_SIGINFO: The signal handler takes three arguments, not one.  In this case,
		 sa_sigaction should be set instead of sa_handler."

	-	Then, the server will pause until it receives a signal.

	-	Finally, return 0.
*/

int main(int argc, char *argv[]) {
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("%sUsage: %s%s\n", RED, argv[0], END);
		return (1);
	}
	ft_printf("%sThe server is ready and running [PID: %d]%s\n\v", CYAN, getpid(), END);
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	while (argc == 1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
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

static void handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	static int	bit_th;
	static int	i;

	(void)ucontext;
	if (sig == SIGUSR1)
		i |= (0x01 << bit_th);
	bit_th++;
	if (bit_th == 8)
	{
		if (i != '\0')
			ft_printf("%c", i);
		else
		{
			ft_printf("\n%sSender:%s %d\n\v", YELLOW, END, (int)(info->si_pid));
			kill(info->si_pid, SIGUSR1);
		}
		bit_th = 0;
		i = 0;
	}
}
