#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

unsigned long	get_timestamp(struct timeval t0)
{
	struct timeval	t1;

	gettimeofday(&t1, NULL);
	return ((t1.tv_sec - t0.tv_sec) * 1000 + (t1.tv_usec - t0.tv_usec) / 1000);
}

int main()
{
	struct timeval t0;
	long int i;

	i = 0;
	gettimeofday(&t0, NULL);
	while (i < 1000)
	{
		printf("%lu\n", get_timestamp(t0));
		usleep(200 * 1000);
		i++;
	}
}
