/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_and_checks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:40:23 by cesar             #+#    #+#             */
/*   Updated: 2024/03/19 17:05:30 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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

int	check_meals(t_ph *ph, pthread_mutex_t print_mut)
{
	if (!ph->table->max_meals)
		return (0);
	if (ph->table->max_meals != 0 && ph->meals >= ph->table->max_meals)
	{
		print_death(ph, print_mut);
		pthread_mutex_lock(&ph->table->famine_mut);
		ph->table->famine = 1;
		pthread_mutex_unlock(&ph->table->famine_mut);
		return (-1);
	}
	return (0);
}

int	yousleep(t_ph *ph, float ms)
{
	struct timeval	current;
	struct timeval	start;
	float			elapsed_time;

	gettimeofday(&start, NULL);
	usleep((ms * 1000) * 0.90);
	while (1)
	{
		if (check_death(ph) == 1)
			return (-1);
		usleep(150);
		gettimeofday(&current, NULL);
		elapsed_time = ((current.tv_sec - start.tv_sec) * 1000)
			+ ((current.tv_usec - start.tv_usec) / 1000);
		if (elapsed_time >= ms)
			return (0);
	}
}
