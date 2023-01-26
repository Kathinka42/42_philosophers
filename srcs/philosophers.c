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
	// while (philo->param->philo_died == false)
	while (i < philo->param->nb_of_philos)
	{
		philo_sleep(philo);
		philo_eat(philo);
		// i++;
	}
	calculate_timestamp_milliseconds(philo->param);
	return (0);
}

/* P_thread join is making pthread create wait for the termination of the thread. After
*	return from pthread_join, we know the thread has finished its execution. You need two
*	while loops one for create, one for join, else ther won't be any threads working in
*	parallel, but only consecutively.
*/
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
	check_starvation(param);
	printf("Failed to join thread");
	while (i < param->nb_of_philos)
	{
		if(pthread_join(p[i], NULL) != 0)
		{
			printf("Failed to join thread");
		}
		// printf("Thread %d has finished its execution\n", param->philo[i]->philo_nb);
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
