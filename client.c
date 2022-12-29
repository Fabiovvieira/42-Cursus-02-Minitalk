#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc > 1)
	{
		pid = atoi(argv[1]);
		printf("sending 10 SIGUSR1\n");
		while (i < 9)
		{
			kill(pid, SIGUSR1);
			usleep(1);
			i++;
		}
		kill(pid, SIGUSR2);
	}
	return(0);
}
