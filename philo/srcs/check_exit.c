/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 12:00:11 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/07 10:04:48 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	CHECK_DEATH
*	------------
*	function checks if too much time has passed between beginning of last meal
*	and now and philo has died. 
*/

void	check_death(t_param *param, int i)
{
	pthread_mutex_lock(&param->exit);
	if ((calculate_timestamp_milliseconds(param) - param->philo[i]->last_meal) \
		> param->time_to_die)
	{
		param->philo_died = true;
		pthread_mutex_unlock(&param->exit);
		philo_print(param->philo[i], "died");
	}
	else
	{
		pthread_mutex_unlock(&param->exit);
		usleep(10);
	}
}

/*	CHECK_NB_MEALS
*	---------------
*	if no parameter for nb of meals is set, function returns 0. Else it counts
*	from the first philo onwards, if the number of meals has been reached. It
*	returns the number of philos that have comleted their meals until the first
*	that has not.
*/

int	check_nb_meals(t_param *param)
{
	int	i;

	i = 0;
	if (param->nb_philo_must_eat < 0)
		return (0);
	pthread_mutex_lock(&param->exit);
	while (i < param->nb_of_philos && param->philo[i]->nb_of_meals \
			>= param->nb_philo_must_eat)
		i++;
	pthread_mutex_unlock(&param->exit);
	return (i);
}

/*	CHECK_EXIT
*	-----------
*	function runs in the main process, in parallel to the threads and checks
*	for the two terminating conditions: whether a philo dies or all philos
*	reached the number of meals required.
*/

void	check_exit(t_param *param)
{
	int	i;

	while (param->nb_meals_reached == false)
	{
		i = 0;
		while (i < param->nb_of_philos)
		{
			check_death(param, i);
			if (param->philo_died == true)
				return ;
			i++;
		}
		i = check_nb_meals(param);
		if (i == param->nb_of_philos)
		{
			pthread_mutex_lock(&param->exit);
			param->nb_meals_reached = true;
			pthread_mutex_unlock(&param->exit);
		}
	}
}
