/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:36:41 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/30 14:32:31 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

/*	GET_TIMESSTAMP_MILLISECONDS
*	----------------------------
*	Function converts the values stored in timeval in milliseconds. The tv_sec
*	field  in the struct timeval contains the number of seconds since the epoch
*	(00:00:00 UTC on January 1, 1970), the field tv_usec contains the number of
*	microseconds since the last whole second.
*/

long long	get_timestamp_milliseconds(t_param *param)
{
	struct timeval current_time;
	long long	milliseconds;
	
	gettimeofday(&current_time, NULL);
	milliseconds = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (milliseconds);
}

/*	CALCULATE_TIMESTAMP_MILLISECONDS
*	----------------------------------
*	Function returns the number of milliseconds elapsed since the start of the
*	program.
*/

long long	calculate_timestamp_milliseconds(t_param *param)
{
	return (get_timestamp_milliseconds(param) - param->start_time);
}

/*	SMART_SLEEP
*	-------------
*	Function replaces the usleep function in this program. it constantly checks
*	whether the value of the variable philo_died was set to "true". In this
*	case function returns (1) immediately to inform the other functions about
*	the death.
*/
int	smart_sleep(t_param *param, long long time)
{
	long long i;
	i = get_timestamp_milliseconds(param);
	while (1)
	{
		pthread_mutex_lock(&param->exit);
		// if (param->philo_died == true || param->nb_meals_reached == true)
		if (param->philo_died == true)
		{
			pthread_mutex_unlock(&param->exit);
			return (1);
		}
		pthread_mutex_unlock(&param->exit);
		if ((get_timestamp_milliseconds(param) - i) >= time)
			return (0);
		usleep (50);
	}
}
