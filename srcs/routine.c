/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:49:17 by cesar             #+#    #+#             */
/*   Updated: 2024/03/14 00:29:39 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


int	action(t_ph *ph, int end, int factor)
{
	int	time;

	time = 0;
	while ((time) <= (end * factor))
	{
		if (is_dead(ph) == 1)
			return (-1);
		usleep(50);
		time += 50;
	}
	return (0);
}

int	sleeps(t_ph *ph)
{
	ph->state = 'S';
	printf("Philosopher %ld is sleeping\n", ph->id);
	if (action(ph, ph->TTS, 1000) == -1)
		return (-1);
	return (0);
}

int	eats(t_ph *ph)
{
	printf("Philosopher %ld is eating\n", ph->id);
	pthread_mutex_lock(&ph->time_since_last_meal_mut);
	ph->time_since_last_meal = 0;
	pthread_mutex_unlock(&ph->time_since_last_meal_mut);
	if (action(ph, ph->TTE, 1000) == -1)
		return (-1);
	pthread_mutex_lock(&ph->time_since_last_meal_mut);
	ph->time_since_last_meal = 0;
	pthread_mutex_unlock(&ph->time_since_last_meal_mut);
	ph->table->forks[ph->first_fork] = 0;
	pthread_mutex_unlock(&ph->table->forks_mut[ph->first_fork]);
	ph->table->forks[ph->second_fork] = 0;
	pthread_mutex_unlock(&ph->table->forks_mut[ph->second_fork]);
	return (0);
}

int	thinks(t_ph *ph)
{
	ph->state = 'T';
	printf("Philosopher %ld is thinking\n", ph->id);
	if (action(ph, 500, 1) == -1)
		return (-1);
	return (0);
}

int	raise_forks(t_ph *ph)
{
	pthread_mutex_lock(&ph->table->forks_mut[ph->first_fork]);
	if (is_dead(ph) == 1)
			return (-1);
	ph->table->forks[ph->first_fork] = 1;
	printf("Philosopher %ld has raised a fork\n", ph->id);
	pthread_mutex_lock(&ph->table->forks_mut[ph->second_fork]);
	if (is_dead(ph) == 1)
			return (-1);
	ph->table->forks[ph->second_fork] = 1;
	printf("Philosopher %ld has raised a fork\n", ph->id);
	ph->state = 'E';
	return (0);
}

void	*routine(void *ph_struct)
{
	t_ph	*ph;
	
	ph = (t_ph *)ph_struct;
	wait_to_start(ph);
	while (1)
	{           
		if (ph->state != 'T')
		{
			if (thinks(ph) == -1)
				return (NULL);
		}
		if (raise_forks(ph) == -1)
			return (NULL);
		if (eats(ph) == -1)
			return (NULL);
		if (sleeps(ph) == -1)
			return (NULL);
	}
	return (NULL);
}
