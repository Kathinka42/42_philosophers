/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:47 by kczichow          #+#    #+#             */
/*   Updated: 2023/01/23 16:23:35 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

// int	allocate_memory(t_param *param)
// {
// 	t_philo *philo;
// 	philo = param->philo;
// 	if(!(philo = malloc(sizeof(t_philo))))
// 		clean_up(param);
// 	return (0);
// }

int	clean_up(t_param *param)
{
	if (param->philo)
		free (param->philo);
	if (param)
		free (param);
	exit (0);
}