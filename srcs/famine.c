/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   famine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:50:06 by cesar             #+#    #+#             */
/*   Updated: 2024/03/14 13:21:47 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*famine(void *ph_struct)
{
	t_ph	*ph;
	struct timeval time;

	ph = (t_ph *)ph_struct;
	wait_to_start(ph);
	while (ph->time_since_last_meal <= ph->TTD * 1000)
	{
		if (is_dead(ph))
			return (NULL);
		pthread_mutex_lock(&ph->time_since_last_meal_mut);
		ph->time_since_last_meal += 50;
		pthread_mutex_unlock(&ph->time_since_last_meal_mut);
		usleep(50);
	}
	ph->state = DEAD;
	if (print_state(ph) == -1)
		return (-1);
	pthread_mutex_lock(&ph->table->famine_mut);	
	ph->table->famine = 1;
	pthread_mutex_unlock(&ph->table->famine_mut);
	return (NULL);
}

int	is_dead(t_ph *ph)
{
	if (ph->table->famine == 1)
	{
		pthread_mutex_unlock(&ph->table->forks_mut[ph->first_fork]);
		pthread_mutex_unlock(&ph->table->forks_mut[ph->second_fork]);
		return (1);	
	}
	return (0);
}
