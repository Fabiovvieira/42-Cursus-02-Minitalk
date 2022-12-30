#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int	flag;

void	handle_sigusr1(int sig)
{
	static int	i;
	char		c;
	(void)sig;
	while(i < 8)
	{
		c = c; //convert 8 bits into chrt
	}
	// printf("SIGUSR1 received!\n");
	printf("1\n");
	flag++;
}
void	handle_sigusr2(int sig)
{
	(void)sig;
	// printf("SIGUSR2 received!\n");
	printf("0\n");
	flag++;
}

int	main(void)
{
	int	pid;
	struct sigaction	sa, sa1;
	sa.sa_handler = &handle_sigusr1;
	sa1.sa_handler = &handle_sigusr2;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa1, NULL);

	pid = getpid();
	printf("pid is: %d\n", pid);
	while (1)
	{
		pause();
	}
	return(0);
}
