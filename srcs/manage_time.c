/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:36:41 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/24 14:37:33 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	GET_TIMESSTAMP_MILLISECONDS
*	----------------------------
*	Function converts the values stored in timeval in milliseconds. The tv_sec
*	field  in the struct timeval contains the number of seconds since the epoch
*	(00:00:00 UTC on January 1, 1970), the field tv_usec contains the number of
*	microseconds since the last whole second.
*/

long long	get_timestamp_milliseconds()
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
	param->timestamp = get_timestamp_milliseconds() - param->start_time;
	// printf("timestamp is %lld\n", get_timestamp_milliseconds() - param->start_time);
	return (get_timestamp_milliseconds() - param->start_time);
}

/*	SMART_SLEEP
*	-------------
*	Function replaces the usleep function in this program.
*/
void	smart_sleep(t_param *param, long long time)
{
	long long i;
	i = get_timestamp_milliseconds();
	while (1)
	{
		if ((get_timestamp_milliseconds() - i) >= time)
			break;
		usleep (50);
	}
}
