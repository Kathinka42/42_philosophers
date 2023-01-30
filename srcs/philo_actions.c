/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:49:16 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/30 09:33:18 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	philo_sleep(t_philo *philo)
{
	// philo->param->timestamp = calculate_timestamp_milliseconds(philo->param);
	philo_print(philo, "is sleeping");
	smart_sleep(philo->param, philo->param->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	// if 
	
	// philo->param->timestamp = calculate_timestamp_milliseconds(philo->param);
	pthread_mutex_lock(&philo->param->time);
	philo_print(philo, "is sleeping");
	// smart_sleep(philo->param, philo->param->time_to_die);
	// if ()
	return (0);
}

int philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->param->forks[philo->left_fork]));
	philo_print(philo, "has taken a fork");
	// pthread_mutex_lock(&philo->param->write);
	// printf ("%lld %d has picked up fork #%d \n", philo->param->timestamp, (philo->philo_nb + 1), philo->left_fork + 1);
	// pthread_mutex_unlock(&philo->param->write);
	pthread_mutex_lock(&(philo->param->forks[philo->right_fork]));
	philo_print(philo, "has taken a fork");
	// pthread_mutex_lock(&philo->param->write);
	// printf ("%lld %d has picked up fork #%d\n", philo->param->timestamp, philo->philo_nb + 1, philo->right_fork + 1);
	// pthread_mutex_unlock(&philo->param->write);
	philo_print(philo, "is eating");
	philo->last_meal = philo->param->timestamp;
	philo->nb_of_meals++;
	smart_sleep(philo->param, philo->param->time_to_eat);
	// pthread_mutex_lock(&philo->param->write);
	// printf ("%lld %d has finished eating\n", philo->param->timestamp, philo->philo_nb + 1);
	// pthread_mutex_unlock(&philo->param->write);
	pthread_mutex_unlock(&(philo->param->forks[philo->left_fork]));
	pthread_mutex_unlock(&(philo->param->forks[philo->right_fork]));

	return (0);
}

int	check_exit(t_param *param)
{
	int i;

	i = 0;
	while (1)
	{
		while (i < param->nb_of_philos)
		{
			if ((calculate_timestamp_milliseconds(param) - param->philo[i]->last_meal) > param->time_to_die)
			{
				param->philo_died = true;
				philo_print(param->philo[i], "died");
				clean_up(param);
			}
			i++;
		}
		i = 0;
		while (i < param->nb_of_philos && param->philo[i]->nb_of_meals >= param->nb_philo_must_eat)
			i++;
		if (i == param->nb_of_philos)
		{
			param->nb_meals_reached = true;
			clean_up(param);
		}
	}
	return (0);
}