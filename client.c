#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void	sendstring(int pid, char *str)
{
	char	c;
	char	s;
	int		i;
	int		j;

	i = 1;
	j = 0;
	c = str[0];
	s = 1;
	printf("%d\n", c);
	while(str[j] != '\0')
	{
		c = str[j];
		while(i < 8)
		{
			if ((c & s) == 1)
			{
				kill(pid, SIGUSR1);
				usleep(1);
			}
			if ((c & s) == 0)
			{
				kill(pid, SIGUSR2);
				usleep(1);
			}
			c = c >> i;
		}
		j++;
		i = 1;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc > 1)
	{
		pid = atoi(argv[1]);
		printf("sending 10 SIGUSR1\n");
		sendstring(pid, argv[2]);
		// while (i < 9)
		// {
		// 	kill(pid, SIGUSR1);
		// 	usleep(1);
		// 	i++;
		// }
		// kill(pid, SIGUSR2);
	}
	return(0);
}
