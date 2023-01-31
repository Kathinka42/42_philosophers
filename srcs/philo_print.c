/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:32:39 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/30 15:16:51 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

/*	PHILO_PRINT
*	---------------
*	Generic print function for log printing. Function uses mutexes, to avoid
*	mixed up log messages from several threads at the same time.
*/

void	philo_print(t_philo *philo, char *str)
{
	long long timestamp;
	
	timestamp = 0;
	pthread_mutex_lock(&philo->param->exit);
	if (philo->param->philo_died == false)
	{
		pthread_mutex_unlock(&philo->param->exit);
		pthread_mutex_lock(&philo->param->write);
		timestamp = calculate_timestamp_milliseconds(philo->param);
		printf ("%lld %d %s\n", timestamp, (philo->philo_nb + 1), str);
		pthread_mutex_unlock(&philo->param->write);
	}
	// else
	// 	pthread_mutex_unlock(&philo->param->exit);
	return ;
}
