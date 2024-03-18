/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   famine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:50:06 by cesar             #+#    #+#             */
/*   Updated: 2024/03/18 16:14:38 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*famine(void *ph_struct)
{
	t_ph	*ph;
	pthread_mutex_t	print_mut;
	struct timeval current;
	struct timeval start;
	long elapsed_time;

	ph = (t_ph *)ph_struct;
	print_mut = ph->table->print_mut;
	gettimeofday(&start, NULL);
	while (1)
	{
		// usleep(1);
		gettimeofday(&current, NULL);
        elapsed_time = ((current.tv_sec - start.tv_sec) * 1000) + ((current.tv_usec - start.tv_usec) / 1000);
        if (elapsed_time >= 1)
		{
			pthread_mutex_lock(&ph->time_since_last_meal_mut);
			ph->time_since_last_meal += 1;
			pthread_mutex_unlock(&ph->time_since_last_meal_mut);
			gettimeofday(&start, NULL);
		}
		if (ph->time_since_last_meal >= ph->TTD)
			return (death(ph, print_mut)); 
		if (check_death(ph) == 1)
			return (NULL);
	} 
}

void	*death(t_ph *ph, pthread_mutex_t print_mut)
{
	print_death(ph, print_mut);
	pthread_mutex_lock(&ph->table->famine_mut);	
	ph->table->famine = 1;
	pthread_mutex_unlock(&ph->table->famine_mut);
	return (NULL);
}
