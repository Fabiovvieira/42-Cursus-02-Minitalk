#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

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
		printf("%d\n", c);
		while(i < 8)
		{
			if ((c & 1) == 1)
			{
				kill(pid, SIGUSR1);
				usleep(10);
			}
			if ((c & 1) == 0)
			{
				kill(pid, SIGUSR2);
				usleep(10);
			}
			c = c >> 1;
			i++;
		}
		j++;
		i = 0;
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
		// printf("sending 10 SIGUSR1\n");
		sendstring(pid, argv[2]);
	}
	return(0);
}
