/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:42:47 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/07 11:41:31 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	CHECK_INPUT
*	---------------
*	checks input from command line and returns error messages.
*/

int	check_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		write(STDERR_FILENO, ERROR_1, ft_strlen(ERROR_1));
		return (1);
	}
	if (philo_atoi(argv[1]) < 0 || philo_atoi(argv[2]) < 0 || \
		philo_atoi(argv[3]) < 0 || philo_atoi(argv[4]) < 0)
	{
		write (STDERR_FILENO, ERROR_2, ft_strlen(ERROR_2));
		return (1);
	}
	if (argc == 6 && philo_atoi(argv[5]) < 0)
	{
		write (STDERR_FILENO, ERROR_2, ft_strlen(ERROR_2));
		return (1);
	}
	return (0);
}

/*	INIT_VARIABLES
*	---------------
*	Initialize variables.
*/

void	init_variables(t_param *param, int argc, char **argv)
{
	param->nb_of_philos = philo_atoi(argv[1]);
	param->time_to_die = philo_atoi(argv[2]);
	param->time_to_eat = philo_atoi(argv[3]);
	param->time_to_sleep = philo_atoi(argv[4]);
	param->nb_philo_must_eat = -1;
	if (argc == 6)
		param->nb_philo_must_eat = philo_atoi(argv[5]);
	param->start_time = get_timestamp_milliseconds(param);
	param->philo_died = false;
	param->nb_meals_reached = false;
}

/*	INIT_PHILO
*	-----------
*	Function creates a struct for each philosopher, allocates memory for that
*	struct and assigns a left and a right fork to each of the philosophers.
*	The identifier (number) for each right fork equals the ID of the
*	philosopher. The identifier of the left fork equals the ID of the
*	philosopher sitting to the left, i.e ID - 1. For the last philosopher
*	obviously the identifier of the left fork equals the ID of Max_philos.
*/

void	init_philo(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->nb_of_philos)
	{
		param->philo[i]->philo_nb = i;
		param->philo[i]->left_fork = i;
		param->philo[i]->right_fork = i + 1;
		param->philo[i]->param = param;
		param->philo[i]->last_meal = 0;
		param->philo[i]->nb_of_meals = 0;
		i++;
	}
	param->philo[param->nb_of_philos - 1]->right_fork = 0;
}
