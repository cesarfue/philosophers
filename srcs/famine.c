/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   famine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:50:06 by cesar             #+#    #+#             */
/*   Updated: 2024/03/18 10:09:14 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*famine(void *ph_struct)
{
	t_ph	*ph;

	ph = (t_ph *)ph_struct;
	while (1)
	{
		action(ph, 10);
		pthread_mutex_lock(&ph->time_since_last_meal_mut);
		ph->time_since_last_meal += 10;
		pthread_mutex_unlock(&ph->time_since_last_meal_mut);
		if (check_death(ph) == 1)
			return (NULL);
		if (ph->time_since_last_meal >= ph->TTD)
			return (death(ph)); 
	} 
}

void	*death(t_ph *ph)
{
	print_death(ph);
	pthread_mutex_lock(&ph->table->famine_mut);	
	ph->table->famine = 1;
	pthread_mutex_unlock(&ph->table->famine_mut);
	return (NULL);

}
