/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:36:12 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/24 10:49:17 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static int count = 0;
pthread_mutex_t lock;
sem_t	semaphore;

void	*function(void *args)
{
	// print thread identifier: this shouldn't be done, because
	// the data type is opaque thread, which means that it could be anything, from int to long long:
	// but you can assign threads ot threads;
	// the thraed identifier is different form the process pid (tid in case of threads); it is also used on
	
	// pthread_t th = pthread_self();
	// printf("%ul\n", th);
	pthread_mutex_lock(&lock);
	//count++;
	//printf("count is: %d\n", count);
	sem_wait(&semaphore);
	sleep (3);
	printf("Philo #%d calling\n", *(int*)args);
	// printf("Philo #%d finishing\n", count);
	
	pthread_mutex_unlock(&lock);
	sem_post(&semaphore);
	free (args);
	return (0);
}

int main ()
{
	int i;
	i = 0;
	pthread_t p[3];
	sem_init(&semaphore, 0, 1);
	// pthread_t p2;
	int nb_of_philos;
	nb_of_philos = 3;
	int *a;


	if (pthread_mutex_init(&lock, NULL))
		return (1);
	
	// exit (0);
	while (i < nb_of_philos)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&p[i], NULL, &function, a) != 0)
			return (i);
		// printf("%ul\n", p[i]);
		i++;
		
	}
	// pthread_create(&p2, NULL, &function, NULL);
	// wait for threads

	i = 0;
	while (i < nb_of_philos)
	{
		if (pthread_join(p[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	// pthread_join(p[0], NULL);
	// pthread_join(p[1], NULL);
	sem_destroy(&semaphore);
	return (0);
}