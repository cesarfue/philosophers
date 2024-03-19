/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:05:10 by cefuente          #+#    #+#             */
/*   Updated: 2024/03/19 12:20:03 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	wait_to_start(t_ph *ph)
{
	pthread_mutex_lock(&ph->starter_mut);
	pthread_mutex_unlock(&ph->starter_mut);
}

void	define_hand(t_ph *ph, int num_ph)
{
	if (ph->id % 2 != 0)
	{
		ph->first_fork = (ph->index + 1 ) % num_ph;
		ph->second_fork = (ph->index % num_ph);
	}
	else
	{
		ph->first_fork = (ph->index % num_ph);
		ph->second_fork = (ph->index + 1) % num_ph;
	}
}

int	atosi(const char *str, int *ret)
{
	size_t	i;
	int		x;
	long	nb;

	i = 0;
	x = 1;
	nb = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nb = nb * 10 + (str[i++] - '0');
	}
	nb *= x;
	if (nb > INT_MAX || nb < INT_MIN)
		return (-1);
	return (*ret = (int)nb);
}

