# include "philo.h"

void	philo_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->param->write);
	philo->param->timestamp = calculate_timestamp_milliseconds(philo->param);
	printf ("%lld %d %s\n", philo->param->timestamp, philo->philo_nb, str);
	pthread_mutex_unlock(&philo->param->write);
	return ;
}