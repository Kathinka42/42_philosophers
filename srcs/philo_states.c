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
	long long time;
	
	// pthread_mutex_lock(&philo->param->write);
	pthread_mutex_lock(&philo->think);
	philo->param->timestamp = calculate_timestamp_milliseconds(philo->param);
	printf ("%lld %d is sleeping\n", philo->param->timestamp, philo->philo_nb);
	// pthread_mutex_unlock(&philo->param->write);
	pthread_mutex_unlock(&philo->think);
	smart_sleep(philo->param, philo->param->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo)
{
	
	return (0);
}

// int philo_eat(t_philo *philo)
// {
// 	if (philo->left_fork == )
// }