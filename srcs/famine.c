/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   famine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:50:06 by cesar             #+#    #+#             */
/*   Updated: 2024/03/12 10:25:22 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*famine(void *ph_struct)
{
	t_ph	*ph;

	ph = (t_ph *)ph_struct;
	wait_the_others(ph);
	usleep(ph->TTD);
	if (ph->state != 'E')
	{
		printf("Philosopher %ld(%c) has died\n", ph->id, ph->state);
		ph->state = 'D'; 
		// exit(0);
	}
	return (NULL);
}

int	is_dead(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < (int)ph->table->num_ph)
	{
		if (((t_ph **)ph->table->ph)[i]->state == 'D')
			return (quit_app(ph), 1);
		i++;
	}
	return (0);
}
