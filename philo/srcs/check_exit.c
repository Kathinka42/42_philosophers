
# include "philo.h"


void	check_death(t_param *param, int i)
{
    pthread_mutex_lock(&param->exit);
	if ((calculate_timestamp_milliseconds(param) - param->philo[i]->last_meal) > param->time_to_die)
	{
		pthread_mutex_unlock(&param->exit);
		philo_print(param->philo[i], "died");
		pthread_mutex_lock(&param->exit);
		param->philo_died = true;
		pthread_mutex_unlock(&param->exit);
	}
	else
	{
		pthread_mutex_unlock(&param->exit);
		smart_sleep(param, 50);
	}
}

void	check_exit(t_param *param)
{
	int i;

	while (param->nb_meals_reached == false)
	{
		i = 0;
		while (i < param->nb_of_philos)
		{
		    check_death(param, i);
		    i++;
		}
		if (param->philo_died == true)
			break;
		i = 0;
		pthread_mutex_lock(&param->exit);
		while (i < param->nb_of_philos && param->philo[i]->nb_of_meals >= param->nb_philo_must_eat)
			i++;
		pthread_mutex_unlock(&param->exit);
		if (i == param->nb_of_philos)
		{
			pthread_mutex_lock(&param->exit);
			param->nb_meals_reached = true;
			pthread_mutex_unlock(&param->exit);
		}
	}
}
