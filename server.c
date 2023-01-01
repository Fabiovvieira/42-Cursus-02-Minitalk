#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void	handle_sig(int sig)
{
	static int		i;
	static char		c;

	if (sig == SIGUSR1)
		c = c | (1 << i);
	i++;
	if (i == 8)
	{
		i = 0;
		write(1, &c, 1);
		c = 0;
	}
}


int	main(void)
{
	int	pid;
	struct sigaction	sa;
	sa.sa_handler = &handle_sig;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	pid = getpid();
	printf("pid is: %d\n", pid);
	while (1)
	{
		pause();
	}
	return(0);
}
