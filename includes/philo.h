/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:03:49 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/24 15:48:49 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define	PHILO_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>

typedef struct s_philo
{
	int				philo_nb;
	int				left_fork;
	int				right_fork;
	int				nb_of_meals;
	long long		last_meal;
	struct s_param	*param;
	pthread_mutex_t	think;
} t_philo;

typedef struct s_param
{
	int			nb_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_philo_must_eat;
	bool		philo_died;
	long long	timestamp;
	long long	start_time;
	pthread_mutex_t write;
	pthread_mutex_t	*forks;
	t_philo		**philo;
} t_param;

// manage_memory and initializze variables
// void	allocate_memory(t_param *param);
void		allocate_philo(t_param *param);
int			clean_up(t_param *param);
void		init_mutexes(t_param *param);
void		destroy_mutexes(t_param *param);
void		init_variables(t_param *param, int argc, char **argv);
void		init_philo(t_param *param);

// manage time
long long	calculate_timestamp_milliseconds(t_param *param);
long long	get_timestamp_milliseconds();
void		smart_sleep(t_param *param, long long time);

// execute actions
int			philo_sleep(t_philo *philo);
int			philo_think(t_philo *philo);
int			philo_eat(t_philo *philo);

void		philo_print(t_philo *philo, char *str);
int			check_starvation(t_param *param);
#endif