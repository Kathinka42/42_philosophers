/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:12 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/23 16:30:17 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

// void	philo_eat(t_param *param)
// {
	
// }

long long	get_timestamp()
{
	struct timeval current_time;
	
	gettimeofday(&current_time, NULL);
	printf("time is %ld\n",(current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
	return ((current_time.tv_sec *1000)- (current_time.tv_usec / 1000));
	
}
void	philo_sleep(t_param *param)
{
	get_timestamp();
	
}


void	*execute_tasks(void *arg)
{
	t_param *param;
	param = arg;
	printf("Philo # %d calling\n", *(int*)arg);
	philo_sleep(param);
	free (arg);
	return (0);
}

void	create_threads(t_param *param)
{
	pthread_t p[param->nb_of_philos];
	int i;
	int *a;

	i = 1;
	while (i <= param->nb_of_philos)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&p[i], NULL, &execute_tasks, a) != 0)
			printf("Thread not created");
		i++;
	}
	i = 1;
	while (i <= param->nb_of_philos)
	{
		if(pthread_join(p[i], NULL) != 0)
			printf("Failed to join thread");
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
	
	param = malloc(sizeof (param));
	if (!param)
		return (1);
	// check_input(argc, argv);
	// allocate_memory(param);
	init_variables(param, argc, argv);
	init_philo(param);
	philosophers(param);
	// clean_up(param);
}