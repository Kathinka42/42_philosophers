/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_for_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:30:57 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/06 15:32:47 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dinner_for_one(t_philo *philo)
{
	pthread_mutex_lock(&(philo->param->forks[philo->left_fork]));
	philo_print(philo, "has taken a fork");
	pthread_mutex_unlock(&(philo->param->forks[philo->left_fork]));
	usleep (philo->param->time_to_die + 5);
	return ;
}
