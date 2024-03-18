/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:05:10 by cefuente          #+#    #+#             */
/*   Updated: 2024/03/16 16:04:55 by cesar            ###   ########.fr       */
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

