/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kczichow <kczichow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:04:22 by kczichow          #+#    #+#             */
/*   Updated: 2023/02/01 16:52:49 by kczichow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*	PHILO_ATOI
*	-----------
*	returns -1 if arguments entered are negative or non digit.
*/

int	philo_atoi(const char *str)
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
		return (-1);
	if (str[i] == '+')
		i++;
	if (str[i] <= '0' || str[i] >= '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
	number = number * 10 + str[i] - '0';
	i++;
	}
	return (number * sign);
}

/*	FT_STRLEN
*	-----------
*	original from libft.
*/

unsigned long	ft_strlen(const char *s)
{
	unsigned long	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*	FT_BZERO
*	-----------
*	original from libft.
*	The ft_bzero() function writes len zeroed bytes to the string str. An empty
*	string is not being considered and leads to segfault.
*/

void	*ft_bzero(void *str, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)str)[i] = '\0';
		i++;
	}
	return (str);
}

/*	FT_CALLOC
*	-----------
*	original from libft.
*	The function allocates memory like malloc, but deletes everything that
*	might already be written in there. It uses bzero to do this.
*/

void	*ft_calloc(size_t	count, size_t	size)
{
	void	*ptr;

	if (size != 0 && 18446744073709551615UL / size < count)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, (count * size));
	return (ptr);
}
