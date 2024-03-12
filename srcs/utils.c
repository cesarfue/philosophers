/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:05:10 by cefuente          #+#    #+#             */
/*   Updated: 2024/03/12 09:54:34 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_ready(t_ph *ph)
{
	size_t	i; 

	i = 0;
	while (i < ph->table->num_ph)
	{
		if (((t_ph *)(ph->table->ph[i]))->ready == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}
void	wait_the_others(t_ph *ph)
{
	while (check_ready(ph) == 0)
	{
		usleep(10);
	}
}

void	define_hand(t_ph *ph, int num_ph)
{
	if (ph->id % 2 == 0)
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
