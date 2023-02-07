/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:12 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/07 13:27:56 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	ENJOY_DINNER
*	-------------
*	holds the while loop to call the think, eat and sleep functions.
*	That loop ends, when either one of the philosophers dies or all
*	philosophers have eaten the given number of times.
*/

void	enjoy_dinner(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->param->exit);
		if (philo->param->nb_meals_reached == false)
		{
			pthread_mutex_unlock(&philo->param->exit);
			if (philo_think(philo))
				return ;
			if (philo_eat(philo))
				return ;
			if (philo_sleep(philo))
				return ;
		}
		else
		{
			pthread_mutex_unlock(&philo->param->exit);
			return ;
		}
	}
}

/*	EXECUTE_TASKS
*	---------------
*	Function is main handler for pthread_create. Philos with even IDs are sent
*	to sleep, to slightly asynchronize the start times to avoid a deadlock.
*	If there's only one philo, it calls a separate function.
*/

void	*execute_tasks(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->param->nb_of_philos == 1)
	{
		dinner_for_one(philo);
		return (NULL);
	}
	if (!philo->philo_nb % 2)
		smart_sleep(philo->param, 20);
	if (philo->param->nb_of_philos % 2 == 1 && philo->philo_nb == 3)
		smart_sleep(philo->param, 60);
	enjoy_dinner(philo);
	return (NULL);
}

/*	PHILOSOPHERS
*	-------------
*	function to create the threads. After return from pthread_join, we know the
*	thread has finished its execution. You need two while loops one for create,
*	one for join, else	there won't be any threads working in parallel, but
*	only consecutively.
*/

void	philosophers(t_param *param)
{	
	pthread_t	*p;
	int			i;

	i = 0;
	p = ft_calloc(sizeof(pthread_t), param->nb_of_philos);
	if (!p)
		return ;
	pthread_mutex_lock(&param->exit);
	while (i < param->nb_of_philos)
	{
		if (pthread_create(&p[i], NULL, &execute_tasks, param->philo[i]) != 0)
			write(STDERR_FILENO, "Thread not created", 18);
		i++;
	}
	pthread_mutex_unlock(&param->exit);
	check_exit(param);
	i = 0;
	while (i < param->nb_of_philos)
	{
		if (pthread_join(p[i], NULL) != 0)
			write(STDERR_FILENO, "Failed to join thread", 21);
		i++;
	}
	free (p);
}

/*	MAIN
*	------
*	Calls functions to initialize variables and to allocate memory, as well
*	as function to clean up after execution of the program.
*/

int	main(int argc, char **argv)
{
	t_param	*param;

	param = ft_calloc(sizeof(t_param), 1);
	if (!param)
		clean_up(param);
	if (check_input(argc, argv))
		return (clean_up(param));
	init_variables(param, argc, argv);
	if (init_mutexes(param))
		return (clean_up (param));
	if (allocate_philo(param))
		return (clean_up (param));
	init_philo(param);
	philosophers(param);
	clean_up(param);
	return (0);
}
