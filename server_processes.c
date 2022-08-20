#include "minitalk.h"

void	ft_reset_sd(t_s_data *g_sd)
{
	g_sd->bit_i = 0;
	g_sd->power_of_two = 1;
	g_sd->client_pid = 0;
	g_sd->client_pid_received = 0;
	g_sd->symbol = 0;
	g_sd->part_to_print[0] = '\0';
	g_sd->symbol_i = 0;
	g_sd->message_received = 0;
}

void	ft_client_pid_receive(t_s_data *g_sd, short signal)
{
	g_sd->bit_i++;
	g_sd->client_pid += signal * g_sd->power_of_two;
	g_sd->power_of_two *= 2;
	if (g_sd->bit_i == 16)
	{
		g_sd->power_of_two = 1;
		g_sd->client_pid_received = 1;
		g_sd->bit_i = 0;
		kill(g_sd->client_pid, SIGUSR1);
	}
}

static void	ft_symbol_received_ok(t_s_data *g_sd)
{
	g_sd->bit_i = 0;
	g_sd->power_of_two = 1;
	g_sd->part_to_print[g_sd->symbol_i] = g_sd->symbol;
	if (g_sd->symbol_i < BUFF_SIZE - 1)
		g_sd->symbol_i++;
	else
	{
		write(1, g_sd->part_to_print, BUFF_SIZE);
		g_sd->symbol_i = 0;
	}
	if (g_sd->symbol == '\0')
	{
		g_sd->message_received = 1;
		g_sd->symbol = 0;
		write(1, g_sd->part_to_print, g_sd->symbol_i);
		write(1, "\n", 1);
		kill(g_sd->client_pid, SIGUSR2);
	}
	else
	{
		g_sd->symbol = 0;
		kill(g_sd->client_pid, SIGUSR1);
	}
}

void	ft_symbol_receive(t_s_data *g_sd, short signal)
{
	g_sd->bit_i++;
	g_sd->symbol += signal * g_sd->power_of_two;
	g_sd->power_of_two *= 2;
	if (g_sd->bit_i == CHAR_SIZE)
		ft_symbol_received_ok(g_sd);
	else
		kill(g_sd->client_pid, SIGUSR1);
}
