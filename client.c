#include "minitalk.h"

t_c_data	g_cd;

static void	ft_send_client_pid(void)
{
	unsigned short	pid;

	pid = getpid();
	while (g_cd.bit_i < 16)
	{
		if (pid % 2)
			kill(g_cd.server_pid, SIGUSR1);
		else
			kill(g_cd.server_pid, SIGUSR2);
		usleep(20);
		pid /= 2;
		g_cd.bit_i++;
	}
	g_cd.bit_i = 0;
}

static void	ft_send_message(void)
{
	if (!g_cd.message[g_cd.symbol_i] && !g_cd.bit_i)
		g_cd.symbol = '\0';
	if (g_cd.bit_i == CHAR_SIZE)
	{
		g_cd.bit_i = 0;
		g_cd.symbol_i++;
		g_cd.symbol = g_cd.message[g_cd.symbol_i];
	}
	if (g_cd.symbol % 2)
	{
		kill(g_cd.server_pid, SIGUSR1);
	}
	else
	{
		kill(g_cd.server_pid, SIGUSR2);
	}
	g_cd.symbol /= 2;
	g_cd.bit_i++;
	usleep(500);
}

static void	ft_server_signal_one(int signal)
{
	(void)signal;
	if (!g_cd.client_pid_received)
	{
		g_cd.client_pid_received = 1;
		g_cd.bit_i = 0;
	}
	ft_send_message();
}

static void	ft_server_signal_zero(int signal)
{
	(void)signal;
	g_cd.message_received = 1;
	write(1, "OK #message was delivered\n", 26);
	exit(0);
}

int	main(int argc, char **argv)
{
	sigset_t			signal;
	struct sigaction	action_one;
	struct sigaction	action_zero;

	if (argc != 3)
	{
		write(1, "ERROR #invalid parameters\n", 26);
		return (0);
	}
	ft_memset(&action_one, 0, sizeof(action_one));
	action_one.sa_handler = ft_server_signal_one;
	sigaction(SIGUSR1, &action_one, NULL);
	sigaddset(&signal, SIGUSR1);
	ft_memset(&action_zero, 0, sizeof(action_zero));
	action_zero.sa_handler = ft_server_signal_zero;
	sigaction(SIGUSR2, &action_zero, NULL);
	sigaddset(&signal, SIGUSR2);
	sigemptyset(&signal);
	ft_reset_cd(&g_cd, ft_pid_atoi(argv[1]), argv[2]);
	ft_send_client_pid();
	ft_c_waiting_for_result(&g_cd);
}
