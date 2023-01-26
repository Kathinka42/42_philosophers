/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:42:47 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/24 16:13:52 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	ft_atoi(char *str)
// {

// }


// void	check_input(int argc, char **argv, t_param *param)
// {
// 	if (argc != 5 && argc != 6)
// 		clean_up(param);
// 	if (ft_atoi(argv[1]) < 2 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
// 		clean_up(param);
// 	if (argc == 6 && ft_atoi(argv[5] < 0)
// 		clean_up(param);
// }


/*	INIT_VARIABLES
*	---------------
*	Initialize variables.
*/

void init_variables(t_param *param, int argc, char **argv)
{
	// param->nb_of_philos = ft_atoi(argv[1]);
	// param->time_to_die = ft_atoi(argv[2]);
	// param->time_to_eat = ft_atoi(argv[3]);
	// param->time_to_sleep = ft_atoi(argv[4]);
	param->nb_of_philos = 5;
	param->time_to_die = 200;
	param->time_to_eat = 200;
	param->time_to_sleep = 200;
	// if (argc == 6)
	// 	param->nb_philo_must_eat = ft_atoi(argv[5]);
	// else
	param->nb_philo_must_eat = 2;
	param->start_time = get_timestamp_milliseconds();
	param->timestamp = 0;
	param->philo_died = false;
	init_mutexes(param);
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
	
	i = 0;
	while(i < param->nb_of_philos)
	{
		param->philo[i]->philo_nb = i + 1;
		// printf("Philo number is %d\t", param->philo[i]->philo_nb);
		param->philo[i]->left_fork = i;
		// printf("Philo left_fork is %d\t", param->philo[i]->left_fork);
		param->philo[i]->right_fork = i + 1;
		// printf("Philo right_fork is %d\n", param->philo[i]->right_fork);
		param->philo[i]->param = param;
		param->philo[i]->last_meal = 0;
		param->philo[i]->nb_of_meals = 0;
		i++;
	}
	param->philo[0]->left_fork = param->nb_of_philos;
}
