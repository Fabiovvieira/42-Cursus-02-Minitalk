#include<stdio.h>
#include<unistd.h>
#include<signal.h>

int	flag;

void	handle_sigusr1(int sig)
{
	printf("SIGUSR1 received!\n");
	flag++;
}
void	handle_sigusr2(int sig)
{
	printf("SIGUSR2 received!\n");
	flag++;
}

int	main(void)
{
	int	pid;
	struct sigaction sa, sa1;
	sa.sa_handler = &handle_sigusr1;
	sa1.sa_handler = &handle_sigusr2;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa1, NULL);

	pid = getpid();
	printf("pid is: %d\n", pid);
	while (flag < 40)
	{
		pause();
	}
	printf("Signal received!\n");
	return(0);
}
