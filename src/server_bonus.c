/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:44:29 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/01/02 15:07:48 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minitalk_bonus.h"

void	handle_sig(int sig, siginfo_t *info, void *ucontext)
{
	static int		i;
	static char		c;

	(void)ucontext;
	if (sig == SIGUSR1)
		c = c | (1 << i);
	i++;
	if (i == 8)
	{
		i = 0;
		write(1, &c, 1);
		if (c == '\0')
			kill(info->si_pid, SIGUSR2);
		c = 0;
	}
}


int	main(void)
{
	int	pid;
	struct sigaction	sa;

	sa.sa_sigaction = &handle_sig;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid = getpid();
	ft_printf("Server pid is: %d\n", pid);
	while (1)
		pause();
	return(0);
}
