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

/*	PHILO_SLEEP
*	-----------
*	calls print function.  Sleep function returns (1), if one of the philos
*	died. This function transports this info by returning (1) in that case.
*/

int	philo_sleep(t_philo *philo)
{
	philo_print(philo, "is sleeping");
	if (smart_sleep(philo->param, philo->param->time_to_sleep))
		return (1);
	return (0);
}

/*	PHILO_THINK
*	-----------
*	only calls function to print thinking log.
*/

int	philo_think(t_philo *philo)
{
	philo_print(philo, "is thinking");
	return (0);
}

/*	PHILO_EAT
*	-----------
*	most complex function called by the handler.uses mutexes to protect the
*	forks from being taken by another philo during mealtime. returns 1, if
*	the return from sleep funciton is (1), i.e. one philo died. else it
*	returns (0). mutex needed to avoid data races, when incrementing the
*	number of meals taken. 
*/

int philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->param->forks[philo->left_fork]));
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->param->forks[philo->right_fork]));
	philo_print(philo, "has taken a fork");
	philo_print(philo, "is eating");
	philo->last_meal = calculate_timestamp_milliseconds(philo->param);
	if (smart_sleep(philo->param, philo->param->time_to_eat))
	{
		pthread_mutex_unlock(&(philo->param->forks[philo->left_fork]));
		pthread_mutex_unlock(&(philo->param->forks[philo->right_fork]));
		return (1);
	}
	pthread_mutex_unlock(&(philo->param->forks[philo->left_fork]));
	pthread_mutex_unlock(&(philo->param->forks[philo->right_fork]));
	pthread_mutex_lock(&philo->param->exit);
	philo->nb_of_meals++;
	pthread_mutex_unlock(&philo->param->exit);
	return (0);
}
