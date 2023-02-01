/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:03:49 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/01 17:03:24 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>

# define ERROR_1	"Error: wrong number of arguments\n"
# define ERROR_2	"Error: invalid argument\n"
# define ERROR_3	"Error: mutex initialization failed\n"
# define ERROR_4	"Error: allocation failed\n"
# define ERROR_5	"Error: thread joining in exec_sim failed\n"

typedef struct s_philo
{
	int				philo_nb;
	int				left_fork;
	int				right_fork;
	int				nb_of_meals;
	long long		last_meal;
	struct s_param	*param;
}	t_philo;

typedef struct s_param
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_philo_must_eat;
	bool			philo_died;
	bool			nb_meals_reached;
	long long		start_time;
	pthread_mutex_t	exit;
	pthread_mutex_t	*forks;
	t_philo			**philo;
}	t_param;

// manage_memory and initialize variables
int				check_input(int argc, char **argv, t_param *param);
int				allocate_philo(t_param *param);
int				init_mutexes(t_param *param);
void			init_variables(t_param *param, int argc, char **argv);
void			init_philo(t_param *param);
int				clean_up(t_param *param);
void			destroy_mutexes(t_param *param);

// manage time
long long		calculate_timestamp_milliseconds(t_param *param);
long long		get_timestamp_milliseconds(t_param *param);
int				smart_sleep(t_param *param, long long time);

// execute actions
int				philo_sleep(t_philo *philo);
int				philo_think(t_philo *philo);
int				philo_eat(t_philo *philo);

int				philo_print(t_philo *philo, char *str);
void			check_exit(t_param *param);
void			check_death(t_param *param, int i);

// utils functions
int				philo_atoi(const char *str);
unsigned long	ft_strlen(const char *s);
void			*ft_calloc(size_t	count, size_t	size);

#endif