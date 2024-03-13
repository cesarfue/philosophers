/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:05:10 by cefuente          #+#    #+#             */
/*   Updated: 2024/03/13 17:22:44 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	wait_to_start(t_ph *ph)
{
	pthread_mutex_lock(&ph->table->ready_mut);
	ph->table->ready++;
	pthread_mutex_unlock(&ph->table->ready_mut);
	while (1)
	{
		if (ph->table->ready == ph->table->num_ph * 2)
			break ;
		usleep(10);
	}
	// usleep(1000000);
}

void	wait_to_end(t_ph *ph)
{
	pthread_mutex_lock(&ph->table->ready_mut);
	ph->table->ready--;
	printf("%ld ready : %ld\n", ph->id, ph->table->ready);
	pthread_mutex_unlock(&ph->table->ready_mut);
	while (1)
	{
		if (ph->table->ready == ph->table->num_ph)
			break ;
		usleep(10);
	}
	// usleep(10000);
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
