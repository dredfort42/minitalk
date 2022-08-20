#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

# define BUFF_SIZE 100

typedef struct s_client_data
{
	unsigned short	server_pid;
	short			bit_i;
	char			*message;
	int				symbol_i;
	unsigned int	symbol;
	short			client_pid_received;
	short			message_received;
}					t_c_data;

typedef struct s_server_data
{
	unsigned short		bit_i;
	int					power_of_two;
	unsigned short		client_pid;
	short				client_pid_received;
	unsigned int		symbol;
	char				part_to_print[BUFF_SIZE];
	unsigned short		symbol_i;
	short				message_received;
}						t_s_data;

unsigned short	ft_pid_atoi(const char *str);
void			ft_pid_itoa(unsigned short pid);
void			*ft_memset(void *b, int c, size_t len);
void			ft_reset_cd(t_c_data *g_cd, unsigned short server_pid,
					char *message);
void			ft_c_waiting_for_result(t_c_data *g_cd);
void			ft_reset_sd(t_s_data *g_sd);
void			ft_client_pid_receive(t_s_data *g_sd, short signal);
void			ft_symbol_receive(t_s_data *g_sd, short signal);
#endif
