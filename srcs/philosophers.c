/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:12 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/30 09:17:56 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

/*	EXECUTE_TASKS
*	---------------
*	Function is main handler for pthread_create. Philos with even IDs are sent
*	to sleep, to slightly asynchronize the start times to avoid a deadlock.
*	Then, execution functions are called in an unterminated loop, that only
*	ends, when either one of the philosophers dies or all philosophers have
*	eaten the given number of times.
*/

void	*execute_tasks(void *arg)
{
	t_philo *philo;
	int i;

	philo = arg;
	i = 0;
	// while (i < philo->param->nb_of_philos)
	// {
		if (philo->philo_nb % 2)
			smart_sleep(philo->param, 5);
	// 	i++;
	// }
	// while (philo->param->philo_died == false || philo->param->nb_meals_reached == false)
	while (philo->param->philo_died == false)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	// calculate_timestamp_milliseconds(philo->param);
	return (0);
}

/*	CREATE_THREADS
*	---------------
*	P_thread join is making pthread create wait for the termination of the thread. After
*	return from pthread_join, we know the thread has finished its execution. You need two
*	while loops one for create, one for join, else there won't be any threads working in
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
			write(STDERR_FILENO, "Thread not created", 18);
		i++;
	}
	i = 0;
	check_exit(param);
	// printf("Failed to join thread");
	while (i < param->nb_of_philos)
	{
		if(pthread_join(p[i], NULL) != 0)
			write(STDERR_FILENO, "Failed to join thread", 21);
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
	init_mutexes(param);
	allocate_philo(param);
	init_philo(param);
	philosophers(param);
	clean_up(param);
}
