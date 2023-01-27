/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 09:32:39 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/27 14:16:42 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

/*	PHILO_PRINT
*	---------------
*	Generic print function for log printing. Function prints mutexes, to avoid
*	data races, because param->timestamp is a variable used by all threads and
*	needs to be protected when written to it.
*/

void	philo_print(t_philo *philo, char *str)
{
	if (philo->param->philo_died == false)
	{
		pthread_mutex_lock(&philo->param->write);
		philo->param->timestamp = calculate_timestamp_milliseconds(philo->param);
		printf ("%lld %d %s\n", philo->param->timestamp, (philo->philo_nb + 1), str);
		pthread_mutex_unlock(&philo->param->write);
	}
	return ;
}
