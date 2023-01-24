/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:12 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/24 16:07:45 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	*execute_tasks(void *arg)
{
	t_philo *philo;
	int i;
	
	philo = arg;
	i = 0;
	while (i < philo->param->nb_philo_must_eat)
	{
		philo_sleep(philo);
		// philo_think(philo);
	}
	if (philo->philo_nb == 3)
		smart_sleep(philo->param, philo->param->time_to_sleep);
	calculate_timestamp_milliseconds(philo->param);
	return (0);
}


void	create_threads(t_param *param)
{
	pthread_t p[param->nb_of_philos];
	int i;
	
	i = 0;
	while (i < param->nb_of_philos)
	{
		if (pthread_create(&p[i], NULL, &execute_tasks, param->philo[i]) != 0)
			printf("Thread not created");
		i++;
	}
	i = 0;
	while (i < param->nb_of_philos)
	{
		if(pthread_join(p[i], NULL) != 0)
			printf("Failed to join thread");
		i++;
	}
}

void	philosophers(t_param *param)
{	
	create_threads(param);

}

int main (int argc, char **argv)
{
	t_param *param;
	
	param = malloc(sizeof(t_param));
	if (!param)
		clean_up(param);
	
	// if (!(check_input(argc, argv))
	// 	clean_up(param);
	// allocate_memory();
	init_variables(param, argc, argv);
	allocate_philo(param);
	init_philo(param);
	philosophers(param);
	clean_up(param);
}
