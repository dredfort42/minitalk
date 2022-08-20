#include "minitalk.h"

void	ft_pid_itoa(unsigned short pid)
{
	short				len;
	unsigned short		tmp_n;
	char				str[5];

	len = 0;
	tmp_n = pid;
	while (tmp_n)
	{
		tmp_n /= 10;
		len++;
	}
	str[len--] = '\0';
	while (len + 1)
	{
		str[len--] = pid % 10 + '0';
		pid /= 10;
	}
	while (str[++len])
	{
		write(1, &str[len], 1);
	}
	write(1, "\n", 1);
}

unsigned short	ft_pid_atoi(const char *str)
{
	int				i;
	unsigned short	num;

	i = 0;
	num = 0;
	while (str[i] < '0' || str[i] > '9')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	return (num);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char	*tmp;
	size_t	i;

	tmp = (char *)b;
	i = 0;
	while (i < len)
	{
		tmp[i] = (char)c;
		i++;
	}
	return (b);
}
