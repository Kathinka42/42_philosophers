/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:49:16 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/24 15:56:02 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	philo_sleep(t_philo *philo)
{
	philo->param->timestamp = calculate_timestamp_milliseconds(philo->param);
	philo_print(philo, "is sleeping");
	smart_sleep(philo->param, philo->param->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	philo->param->timestamp = calculate_timestamp_milliseconds(philo->param);
	printf ("%lld %d is thinking\n", philo->param->timestamp, philo->philo_nb);
	smart_sleep(philo->param, philo->param->time_to_die);
	// if ()
	return (0);
}

int philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->param->forks[philo->left_fork]));
	printf ("%lld %d has picked up fork #%d \n", philo->param->timestamp, philo->philo_nb, philo->left_fork);
	pthread_mutex_lock(&(philo->param->forks[philo->right_fork]));
	printf ("%lld %d has picked up fork #%d\n", philo->param->timestamp, philo->philo_nb, philo->right_fork);
	philo_print(philo, "is eating");
	philo->last_meal = philo->param->timestamp;
	philo->nb_of_meals++;
	smart_sleep(philo->param, philo->param->time_to_eat);
	printf ("%lld %d has finished eating\n", philo->param->timestamp, philo->philo_nb);
	pthread_mutex_unlock(&(philo->param->forks[philo->left_fork]));
	pthread_mutex_unlock(&(philo->param->forks[philo->right_fork]));

	// if (philo->left_fork == )
	return (0);
}

int	check_starvation(t_param *param)
{
	int i;

	i = 0;
	while (1)
	{
		while (i < param->nb_of_philos)
		{
			if ((calculate_timestamp_milliseconds(param) - param->philo[i]->last_meal) >  param->time_to_die)
			{
				param->philo_died = true;
				break;
			}
			i++;
		}
		i = 0;
	}
}