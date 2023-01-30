/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:49:16 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/30 16:39:15 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	philo_sleep(t_philo *philo)
{
	if (philo->param->philo_died == false && philo->param->nb_meals_reached == false)
	{
		philo_print(philo, "is sleeping");
		smart_sleep(philo->param, philo->param->time_to_sleep);
	}
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (philo->param->philo_died == false && philo->param->nb_meals_reached == false)
		philo_print(philo, "is thinking");
	return (0);
}

int philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->param->forks[philo->left_fork]));
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->param->forks[philo->right_fork]));
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->param->eat);
	philo_print(philo, "is eating");
	philo->last_meal = calculate_timestamp_milliseconds(philo->param);
	pthread_mutex_unlock(&philo->param->eat);
	smart_sleep(philo->param, philo->param->time_to_eat);
	pthread_mutex_unlock(&(philo->param->forks[philo->left_fork]));
	pthread_mutex_unlock(&(philo->param->forks[philo->right_fork]));
	philo->nb_of_meals++;
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
				pthread_mutex_lock(&param->eat);
				param->philo_died = true;
				philo_print(param->philo[i], "died");
				pthread_mutex_unlock(&param->eat);
				smart_sleep(param, 800);
				return;
				// clean_up(param);
			}
			i++;
		}
		i = 0;
		while (i < param->nb_of_philos && param->philo[i]->nb_of_meals >= param->nb_philo_must_eat)
			i++;
		if (i == param->nb_of_philos)
		{
			param->nb_meals_reached = true;
			pthread_mutex_lock(&param->eat);
			printf("MAX NB OF MEALS REACHED\n");
			pthread_mutex_unlock(&param->eat);
			smart_sleep(param, 200);
			clean_up(param);
		}
	}
	return (0);
}