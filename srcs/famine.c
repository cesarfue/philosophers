/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   famine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:50:06 by cesar             #+#    #+#             */
/*   Updated: 2024/03/15 15:40:21 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*famine(void *ph_struct)
{
	t_ph	*ph;

	ph = (t_ph *)ph_struct;
	wait_to_start(ph);
	while (1)
	{
		action(ph, 10);
		pthread_mutex_lock(&ph->time_since_last_meal_mut);
		ph->time_since_last_meal += 10;
		pthread_mutex_unlock(&ph->time_since_last_meal_mut);
		if (check_death(ph) == 1)
			return (NULL);
		if (ph->time_since_last_meal >= ph->TTD)
			break ; 
	} 
	ph->state = DEAD;
	if (print_state(ph) == -1)
		return (NULL);
	pthread_mutex_lock(&ph->table->famine_mut);	
	ph->table->famine = 1;
	pthread_mutex_unlock(&ph->table->famine_mut);
	return (NULL);
}

int	check_death(t_ph *ph)
{
	if (ph->table->famine == 1)
	{
		// printf("updated\n");
		pthread_mutex_unlock(&ph->table->forks_mut[ph->first_fork]);
		pthread_mutex_unlock(&ph->table->forks_mut[ph->second_fork]);
		return (1);	
	}
	return (0);
}


int	check_meals(t_ph *ph)
{
	if (!ph->table->max_meals)
		return (0);
	if (ph->meals >= ph->table->max_meals)
	{
		ph->state = DEAD;
		if (print_state(ph) == -1)
			return (-1);
		pthread_mutex_lock(&ph->table->famine_mut);
		ph->table->famine = 1;
		pthread_mutex_unlock(&ph->table->famine_mut);
		return (-1);
	}
	return (0);
}
