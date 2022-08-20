#include "minitalk.h"

void	ft_reset_cd(t_c_data *g_cd, unsigned short server_pid, char *message)
{
	g_cd->server_pid = server_pid;
	g_cd->bit_i = 0;
	g_cd->message = message;
	g_cd->symbol_i = 0;
	if (g_cd->message[g_cd->symbol_i])
		g_cd->symbol = g_cd->message[g_cd->symbol_i];
	else
		g_cd->symbol = '\0';
	g_cd->client_pid_received = 0;
	g_cd->message_received = 0;
}

void 	ft_c_waiting_for_result(t_c_data *g_cd)
{
	while (!g_cd->client_pid_received)
	{
		usleep(400);
		if (!g_cd->client_pid_received)
		{
			write(1, "ERROR #no connection to the server\n", 35);
			exit(0);
		}
	}
	while (!g_cd->client_pid_received || !g_cd->message_received)
	{
	}
}
