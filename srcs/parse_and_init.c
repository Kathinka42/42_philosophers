/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:42:47 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/30 09:09:09 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	FT_ATOI
*	-------
*	Original libft function.
*/

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	number;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '-')
			sign = sign * (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
	number = number * 10 + str[i] - '0';
	i++;
	}
	return (number * sign);
}


// void	check_input(int argc, char **argv, t_param *param)
// {
// 	if (argc != 5 && argc != 6)
// 	{
// 		write(STDERR_FILENO, "Wrong number of arguments\n", 26);
// 		clean_up(param);
// 	}
// 	if (ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || ft_atoi(argv[4]) < 0)
// 	{
// 		write (STDERR_FILENO, "Invalid argument", 16);
// 		clean_up(param);
// 	}
// 	if (argc == 6 && ft_atoi(argv[5] < 0)
// 	{
// 		write (STDERR_FILENO, "Invalid argument", 16);
// 		clean_up(param);
// 	}
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
	param->time_to_die = 410;
	param->time_to_eat = 200;
	param->time_to_sleep = 200;
	// if (argc == 6)
	// 	param->nb_philo_must_eat = ft_atoi(argv[5]);
	// else
	param->nb_philo_must_eat = 2;
	param->start_time = get_timestamp_milliseconds();
	param->timestamp = 0;
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
	int i;
	
	i = 0;
	while(i < param->nb_of_philos)
	{
		param->philo[i]->philo_nb = i;
		param->philo[i]->left_fork = i;
		param->philo[i]->right_fork = i + 1;
		param->philo[i]->param = param;
		param->philo[i]->last_meal = 0;
		param->philo[i]->nb_of_meals = 0;
		param->philo[i]->nb_philo_must_eat = param->nb_philo_must_eat;
		i++;
	}
	param->philo[param->nb_of_philos - 1]->right_fork = 0;
}
