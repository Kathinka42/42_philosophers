/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:42:47 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/23 16:30:05 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	INIT_VARIABLES
*	---------------
*	Initialize variables.
*/

void init_variables(t_param *param, int argc, char **argv)
{
	param->nb_of_philos = 5;
	param->time_to_die = 200;
	param->time_to_eat = 200;
	param->time_to_sleep = 200;
	// if (argc == 6)
	// 	param->nb_philo_must_eat = ft_atoi(argv[5]);
	// else
	// 	param->nb_philo_must_eat = 200;
	param->timestamp = 0;
}

/*	INIT_PHILO
*	-----------
*	Function creates a struct for each philosopher, allocates memory for that
*	struct and assigns a left and a right fork to each of the philosophers.
*	The identifier (number) for each right fork equals the ID of the
*	philosopher. The identifier of the left fork equals the ID of the
*	philosopher sitting to the left, i.e ID - 1. For the first philosopher
*	obviously the identifier of the left fork equals the ID of Max_philos.
*/

void	init_philo(t_param *param)
{
	int i;
	t_philo *philo[param->nb_of_philos];
	*philo = param->philo;
	i = 0;
	while(i < param->nb_of_philos)
	{
		if (!(philo[i] = malloc(sizeof(t_philo *))))
			clean_up(param);
		philo[i]->philo_nb = i + 1;
		printf("Philo number is %d\t", philo[i]->philo_nb);
		philo[i]->left_fork = i;
		printf("Philo left_fork is %d\t", philo[i]->left_fork);
		philo[i]->right_fork = i + 1;
		printf("Philo right_fork is %d\n", philo[i]->right_fork);
		i++;
	}
	philo[0]->left_fork = param->nb_of_philos;
	printf("Philo number 1 left_fork is %d\n", philo[0]->left_fork);
}