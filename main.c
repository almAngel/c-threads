#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void	*increment_counter(void *arg)
{
	int	thread_id;
	int	i;

	thread_id = *(int *)arg;
	i = 0;
	printf("Hilo %d inicializado\n", thread_id);
	while (i < 100000)
	{
		pthread_mutex_lock(&mutex);
		counter++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	printf("Hilo %d terminado\n", thread_id);
	return (NULL);
}

int	main(void)
{
	pthread_t	threads[4];
	int			thread_ids[4];
	int			i;

	printf("=== INICIO DEL PROGRAMA ===\n");
	printf("Contador inicial: %d\n", counter);
	i = 0;
	while (i < 4)
	{
		thread_ids[i] = i + 1;
		if (pthread_create(&threads[i], NULL, increment_counter, &thread_ids[i]) != 0)
		{
			printf("Error creando hilo %d\n", i + 1);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < 4)
		pthread_join(threads[i++], NULL);
	printf("=== RESULTADO FINAL ===\n");
    printf("Contador final: %d\n", counter);
    printf("Esperado: %d\n", 4 * 100000);
    return (0);
}