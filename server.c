#include "minitalk.h"

t_s_data	g_sd;

static void	ft_client_signal_one(int signal)
{
	(void) signal;
	if (!g_sd.client_pid_received)
		ft_client_pid_receive(&g_sd, 1);
	else if (g_sd.client_pid_received && !g_sd.message_received)
		ft_symbol_receive(&g_sd, 1);
	else
		ft_reset_sd(&g_sd);
}

static void	ft_client_signal_zero(int signal)
{
	(void) signal;
	if (!g_sd.client_pid_received)
		ft_client_pid_receive(&g_sd, 0);
	else if (g_sd.client_pid_received && !g_sd.message_received)
		ft_symbol_receive(&g_sd, 0);
	else
		ft_reset_sd(&g_sd);
}

int	main(void)
{
	sigset_t			client_signals;
	struct sigaction	act_one;
	struct sigaction	act_zero;

	ft_memset(&act_one, 0, sizeof(act_one));
	act_one.sa_handler = ft_client_signal_one;
	sigaction(SIGUSR1, &act_one, NULL);
	sigaddset(&client_signals, SIGUSR1);
	ft_memset(&act_one, 0, sizeof(act_one));
	act_zero.sa_handler = ft_client_signal_zero;
	sigaction(SIGUSR2, &act_zero, NULL);
	sigaddset(&client_signals, SIGUSR2);
	sigemptyset(&client_signals);
	ft_reset_sd(&g_sd);
	ft_pid_itoa(getpid());
	while (1)
	{
		if (g_sd.client_pid_received && g_sd.message_received)
			ft_reset_sd(&g_sd);
	}
}
