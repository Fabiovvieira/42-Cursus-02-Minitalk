/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:44:15 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/01/02 16:41:09 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk_bonus.h"

void	sendstring(int pid, char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while(str[j] != '\0')
	{
		c = str[j];
		while(i < 8)
		{
			if ((c & 1) == 1)
			{
				kill(pid, SIGUSR1);
			}
			else if ((c & 1) == 0)
			{
				kill(pid, SIGUSR2);
			}
			usleep(200);
			c = c >> 1;
			i++;
		}
		j++;
		i = 0;
	}
}
void	send_null(int pid)
{
	int	i;

	i = 0;
	while(i < 8)
	{
		kill(pid, SIGUSR2);
		usleep(200);
		i++;
	}
}

int	check_param(int argc)
{
	int	check;

	check = 0;
	if (argc != 3)
	{
		ft_printf("Please check inputs from ./client: Shoulb be './client 'pid' 'string''");
		exit(0);
	}
	else
		check = 1;
	return (check);
}

void	handle_sig(int sig)
{
	if (sig == SIGUSR2)
		ft_printf("Server received message.\n");
	exit(0);
}

int	main(int argc, char **argv)
{
	int	pid;
	struct sigaction	sa;

	sa.sa_handler = &handle_sig;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR2, &sa, NULL);
	sa.sa_flags = SA_RESTART;
	if (check_param(argc) == 1)
	{
		pid = ft_atoi(argv[1]);
		sendstring(pid, argv[2]);
		sendstring(pid,"\n");
		send_null(pid);
	}
	while (1)
		pause();
	return(0);
}
