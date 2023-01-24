/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:47 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/24 15:37:15 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

/*	ALLOCATE_PHILO
*	---------------
*	Function allocates an array of structs t_philo *, that holds a spot for a
*	struct for each philosopher. It then allocates a struct t_philo for each
*	philosopher.
*/

void	allocate_philo(t_param *param)
{
	int i;
	
	param->philo = malloc(sizeof(t_philo *) * param->nb_of_philos);
	if (!param->philo)
		clean_up(param);
	i = 0;
	while(i < param->nb_of_philos)
	{
		if (!(param->philo[i] = malloc(sizeof(t_philo))))
			clean_up(param);
		i++;
	}
}

/*	CLEAN_UP
*	----------
*	De-allocate all allocated memory. Check for NULL pointers before attempting
*	to access memory.
*/

int	clean_up(t_param *param)
{
	int i;

	i = 0;
	if (param->philo && param)
	{
		while (i < param->nb_of_philos && param->philo[i] != NULL)
		{
			free(param->philo[i]);
			i++;
		}
		free (param->philo);
	}
	if (param)
		free (param);
	exit (0);
}