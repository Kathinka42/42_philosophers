/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:36:12 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/19 15:59:02 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

static int count = 0;
pthread_mutex_t lock;

void	*function()
{
	pthread_mutex_lock(&lock);
	count++;
	printf("count is: %d\n", count);
	printf("Philo #%d calling\n", count);
	sleep (3);
	printf("Philo #%d finishing\n", count);
	
	pthread_mutex_unlock(&lock);
	
	return (0);
}

int main (void)
{
	int i;
	i = 0;
	pthread_t p[3];
	// pthread_t p2;
	int nb_of_philos;
	nb_of_philos = 3;

	if (pthread_mutex_init(&lock, NULL))
		return (1);
	
	// exit (0);
	while (i < nb_of_philos)
	{
		if (pthread_create(&p[i], NULL, &function, NULL) != 0)
			return (i);
		i++;
		
	}
	// pthread_create(&p2, NULL, &function, NULL);
	// wait for threads

	// while (i < nb_of_philos)
	// {
	// 	if (pthread_join(p[i], NULL) != 0)
	// 		return (i);
	// 	i++;
	// }
	pthread_join(p[0], NULL);
	pthread_join(p[1], NULL);
	return (0);
}