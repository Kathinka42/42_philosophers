/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:47 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/01 16:51:29 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	INIT_MUTEXES
*	---------------
*	Function allocates memory for mutexes array. Then uses mutex_init to
*	allocate memory for each individual mutex.
*/

int	init_mutexes(t_param *param)
{
	int	i;

	i = 0;
	param->forks = ft_calloc(sizeof(pthread_mutex_t), param->nb_of_philos);
	if (!param->forks)
	{
		write(2, ERROR_4, ft_strlen(ERROR_4));
		return (1);
	}
	while (i < param->nb_of_philos)
	{
		if (pthread_mutex_init (&param->forks[i], NULL))
		{
			write(2, ERROR_3, ft_strlen(ERROR_3));
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&param->exit, NULL))
	{
		write(2, ERROR_3, ft_strlen(ERROR_3));
		return (1);
	}
	return (0);
}

/*	DESTROY_MUTEXES
*	---------------
*	Function deallocates all memory that was allocated for mutexes.
*	Lib function pthread_mutex_destroy mainly takes care of it.
*/

void	destroy_mutexes(t_param *param)
{
	int	i;

	pthread_mutex_destroy(&param->exit);
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

int	allocate_philo(t_param *param)
{
	int	i;

	param->philo = ft_calloc(sizeof(t_philo), param->nb_of_philos);
	if (!param->philo)
	{
		write (2, ERROR_4, ft_strlen(ERROR_4));
		return (1);
	}
	i = 0;
	while (i < param->nb_of_philos)
	{
		param->philo[i] = malloc(sizeof(t_philo));
		if (!param->philo[i])
		{
			write (2, ERROR_4, ft_strlen(ERROR_4));
			return (1);
		}
		i++;
	}
	return (0);
}

/*	CLEAN_UP
*	----------
*	De-allocate all allocated memory. Check for NULL pointers before attempting
*	to access memory.
*/

int	clean_up(t_param *param)
{
	int	i;

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
	exit (0);
}
