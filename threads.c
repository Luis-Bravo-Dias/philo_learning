#include <stdio.h>
#include <pthread.h>

# define NC "\e[0m"
# define YELLOW "\e[33m"
# define BYELLOW "\e[1;33m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"

#define TIMES_TO_COUNT	21000

void	*thread_routine(void *data)
{
	pthread_t	tid;
	unsigned int	*count;
	unsigned int	i;

	tid = pthread_self();
	printf("%sThread [%ld]: count at thread start = %u.%s\n", YELLOW, tid, *count, NC);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		(*count)++;
		i++;
	}
	printf("%sThread [%d]: Final count = %u.%s\n", BYELLOW, tid, *count, NC);
	return (NULL);
}

int	main(void)
{
	pthread_t	tid1; //first thread's ID
	pthread_t	tid2; //second thread's ID
	unsigned int	count;

	count = 0;
	printf("Main: Expected count is %s%u%s\n", GREEN, 2 * TIMES_TO_COUNT, NC);
	
	pthread_create(&tid1, NULL, thread_routine, &count);
	printf("Main: Created first thread [%ld]\n", tid1);

	pthread_create(&tid2, NULL, thread_routine, &count);
	printf("Main: Created second thread [%ld]\n", tid2);

	pthread_join(tid1, NULL);
	printf("Main: Joined first thread [%d]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Joined second thread [%d]\n", tid2);

	if (count != (2 * TIMES_TO_COUNT))
		printf("%sMain: ERROR! Total count is %u%s\n", RED, count, NC);
	else
		printf("%sMain: Ok. Total count is %u%s\n", GREEN, count, NC);
	return (0);
}