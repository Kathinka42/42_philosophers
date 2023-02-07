/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:32:39 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/07 10:05:04 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	PHILO_PRINT
*	---------------
*	Generic print function for log printing. Function uses mutexes, to avoid
*	mixed up log messages from several threads at the same time.
*/

int	philo_print(t_philo *philo, char *str)
{
	long long	timestamp;

	timestamp = 0;
	pthread_mutex_lock(&philo->param->exit);
	if (philo->param->philo_died == false || !ft_strncmp(str, "died", 5))
	{
		timestamp = calculate_timestamp_milliseconds(philo->param);
		printf ("%lld %d %s\n", timestamp, (philo->philo_nb + 1), str);
		pthread_mutex_unlock(&philo->param->exit);
		return (0);
	}
	else
	{
		pthread_mutex_unlock(&philo->param->exit);
		return (1);
	}
}
