/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   famine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:50:06 by cesar             #+#    #+#             */
/*   Updated: 2024/03/13 17:22:15 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*famine(void *ph_struct)
{
	t_ph	*ph;

	ph = (t_ph *)ph_struct;
	wait_to_start(ph);
	// printf("famine started\n");
	while (is_dead(ph) == 0)
	{
		if (action(ph, ph->TTD, 1000) == -1)
			return (NULL);
		if (ph->state != 'E')
		{
			printf("Philosopher %ld(%c) has died\n", ph->id, ph->state);
			pthread_mutex_lock(&ph->table->famine_mut);	
			ph->table->famine = 1;
			pthread_mutex_unlock(&ph->table->famine_mut);
			return (NULL);
		}
	}
	return (NULL);
}

int	is_dead(t_ph *ph)
{
	if (ph->table->famine == 1)
		return (1);	
	return (0);
}
