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

/*	FT_STRNCMP
*	-------------
*	DESCRIPTION
*	The function lexicographically compares n characters of two strings.
*	Lexicographically bigger or smaller depends on the order in the alphabet
*	(a<b);
*/

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < (n - 1)) && str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] == str2[i])
		i++;
		else
			return ((unsigned char)str1[i] - (unsigned char) str2[i]);
	}
	return ((unsigned char) str1[i] - (unsigned char) str2[i]);
}

/*	PHILO_PRINT
*	---------------
*	Generic print function for log printing. Function uses mutexes, to avoid
*	mixed up log messages from several threads at the same time.
*/

void	philo_print(t_philo *philo, char *str)
{
	long long timestamp;
	
	timestamp = 0;
	if (philo->param->philo_died == false && philo->param->nb_meals_reached == false)
	{
		pthread_mutex_lock(&philo->param->write);
		timestamp = calculate_timestamp_milliseconds(philo->param);
		printf ("%lld %d %s\n", timestamp, (philo->philo_nb + 1), str);
		pthread_mutex_unlock(&philo->param->write);
	}
	else if (philo->param->philo_died == true && !ft_strncmp(str, "died", 5))
	{
		pthread_mutex_lock(&philo->param->write);
		timestamp = calculate_timestamp_milliseconds(philo->param);
		printf ("%lld %d %s\n", timestamp, (philo->philo_nb + 1), str);
		pthread_mutex_unlock(&philo->param->write);
	}
	return ;
}
