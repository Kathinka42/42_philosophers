/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:03:49 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/23 16:27:21 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define	PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo
{
	int			philo_nb;
	int			left_fork;
	int			right_fork;
	
} t_philo;

typedef struct s_param
{
	int			nb_of_philos;
	float		time_to_die;
	float		time_to_eat;
	float		time_to_sleep;
	int			nb_philo_must_eat;
	long long	timestamp;
	t_philo		*philo;
} t_param;


void init_variables(t_param *param, int argc, char **argv);
// int	allocate_memory(t_param *param);
void	init_philo(t_param *param);
int	clean_up(t_param *param);

#endif