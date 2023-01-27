/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:47 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/27 14:14:41 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

/*	INIT_MUTEXES
*	---------------
*	Function allocates memory for mutexes array. Then uses mutex_init to
*	allocate memory for each individual mutex.
*/

void init_mutexes(t_param *param)
{
	int i;

	i = 0;
	param->forks = malloc(sizeof(pthread_mutex_t) * param->nb_of_philos);
	if (!param->forks)
		clean_up(param);
	// exit (0);
	while (i < param->nb_of_philos)
	{
		if(pthread_mutex_init(&param->forks[i], NULL))
		{
			write(2, "Initialization of mutex failed\n", 31);
			clean_up(param);
		}
		i++;
	}
	if (pthread_mutex_init(&param->write, NULL) \
		|| pthread_mutex_init(&param->time, NULL))
	{
		write(2, "Initialization of mutex failed\n", 31);
		clean_up(param);
	}
}

/*	DESTROY_MUTEXES
*	---------------
*	Function deallocates all memory that was allocated for mutexes.
*	Lib function pthread_mutex_destroy mainly takes care of it.
*/

void	destroy_mutexes(t_param *param)
{
	int i;

	pthread_mutex_destroy(&param->write);
	pthread_mutex_destroy(&param->time);
	i = 0;
	while (i < param->nb_of_philos && &param->forks[i] != NULL)
	{
		pthread_mutex_destroy(&param->forks[i]);
		i++;
	}
	free (param->forks);
}

/*	ALLOCATE_PHILO
*	---------------
*	Function allocates an array of structs t_philo *, that holds a spot for a
*	struct for each philosopher. It then allocates a struct t_philo for each
*	philosopher.
*/

void	allocate_philo(t_param *param)
{
	int i;
	
	param->philo = malloc(sizeof(t_philo *) * param->nb_of_philos);
	if (!param->philo)
		clean_up(param);
	i = 0;
	while(i < param->nb_of_philos)
	{
		if (!(param->philo[i] = malloc(sizeof(t_philo))))
			clean_up(param);
		i++;
	}
}

/*	CLEAN_UP
*	----------
*	De-allocate all allocated memory. Check for NULL pointers before attempting
*	to access memory.
*/

int	clean_up(t_param *param)
{
	int i;

	i = 0;
	if (param && param->philo)
	{
		while (i < param->nb_of_philos && param->philo[i] != NULL)
		{
			free(param->philo[i]);
			i++;
		}
		free (param->philo);
	}
	destroy_mutexes(param);
	if (param)
		free (param);
	system ("leaks philo");
	exit (0);
}