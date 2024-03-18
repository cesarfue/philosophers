/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_and_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:40:23 by cesar             #+#    #+#             */
/*   Updated: 2024/03/16 18:23:58 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int action(t_ph *ph, long end)
{
	struct timeval current;
	struct timeval start;
	long elapsed_time;

	gettimeofday(&start, NULL);
	while (1)
	{
		if (check_death(ph) == 1)
			return (-1);
		gettimeofday(&current, NULL);
		elapsed_time = ((current.tv_sec - start.tv_sec) * 1000) + ((current.tv_usec - start.tv_usec) / 1000);
		if (elapsed_time >= end)
			return (0);
		usleep(10);
	}
}

int	check_death(t_ph *ph)
{
	if (ph->table->famine == 1)
	{
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
		print_death(ph);
		pthread_mutex_lock(&ph->table->famine_mut);
		ph->table->famine = 1;
		pthread_mutex_unlock(&ph->table->famine_mut);
		return (-1);
	}
	return (0);
}