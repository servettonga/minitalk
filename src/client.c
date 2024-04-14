#include "minitalk.h"

static void send_message(pid_t pid, char msg);
static void confirm_signal(int sig);
static int ft_atoi(const char *str);

/*
	The client sends a message to the server by sending signals.

	-	First check if the argument count is 3, if not print the usage message.

	-	Then convert the PID from a string to an integer.

	-	Next, set the message to the second argument.

	-	Then, while the message is not empty, send the message to the server.
		The message is sent by sending signals to the server.
		The action for SIGUSR1 is set to confirm_signal.
		Then each character in the message is sent to the server.

	-	Finally, send a null character to the server to indicate the end of the message.

	-	Return 0.
*/

int main(int argc, char *argv[])
{
	pid_t	pid;
	char	*message;

	if (argc != 3)
	{
		ft_printf("%sUsage: %s [PID] [MESSAGE]%s\n", RED, argv[0], END);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	message = argv[2];
	while (*message)
	{
		signal(SIGUSR1, confirm_signal);
		send_message(pid, *message);
		message++;
	}
	send_message(pid, '\0');
	return (0);
}

/*
	The confirm_signal function confirms that the message was sent successfully.

	-	If the signal is SIGUSR1, print a message indicating that the message was sent successfully.
*/

static void	confirm_signal(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("%sMessage sent successfully [PID: %d]%s\n", GREEN, getpid(), END);
}

/*
	The send_message function sends a message to the server by sending signals.

	-	First, set the bit to 0.

	-	Then, while the bit is less than 8, send a signal to the server.

		Takes the number 1 (0x01) and shifts it left by the bit.
		For example: 0x01 << 0 = 0x01, 0x01 << 1 = 0x02, 0x01 << 2 = 0x04, etc.
		Then & operator is used to check if the bit is set in the message.

		If the bit is set in the message, send SIGUSR1.
		Otherwise, send SIGUSR2.

	-	Then sleep for 100 microseconds.

	-	Finally, increment the bit.

*/

static void send_message(pid_t pid, char msg)
{
	int bit;

	bit = 0;
	while (bit < 8)
	{
		if ((msg & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

/*
	Convert a string to an integer.
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
