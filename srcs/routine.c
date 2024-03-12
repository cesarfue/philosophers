/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:49:17 by cesar             #+#    #+#             */
/*   Updated: 2024/03/12 10:02:06 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	action(t_ph *ph, int end)
{
	int	time;

	time = 0;
	while (!is_dead(ph) && time < end)
	{
		usleep(5);
		time += 5;
	}
}


void	sleeps(t_ph *ph)
{
	ph->state = 'S';
	printf("Philosopher %ld is sleeping\n", ph->id);
	action(ph, ph->TTS);
	// usleep(ph->TTE * 1000);
}

void	eats(t_ph *ph)
{
	printf("Philosopher %ld is eating\n", ph->id);
	action(ph, ph->TTE);
	// usleep(ph->TTE * 1000);
	ph->table->forks[ph->first_fork] = 0;
	pthread_mutex_unlock(&ph->table->forks_mut[ph->first_fork]);
	ph->table->forks[ph->second_fork] = 0;
	pthread_mutex_unlock(&ph->table->forks_mut[ph->second_fork]);
}

void	thinks(t_ph *ph)
{
	ph->state = 'T';
	printf("Philosopher %ld is thinking\n", ph->id);
}

void	raise_forks(t_ph *ph)
{
	while (!is_dead(ph) && pthread_mutex_lock(&ph->table->forks_mut[ph->first_fork]) != 0)
		usleep(1);
	// pthread_mutex_lock(&ph->table->forks_mut[ph->first_fork]);
	ph->state = 'H';
	ph->table->forks[ph->first_fork] = 1;
	printf("Philosopher %ld has raised a fork\n", ph->id);
	while (!is_dead(ph) && pthread_mutex_lock(&ph->table->forks_mut[ph->second_fork]) != 0)
		usleep(1);
	// pthread_mutex_lock(&ph->table->forks_mut[ph->second_fork]);
	ph->table->forks[ph->second_fork] = 1;
	printf("Philosopher %ld has raised a fork\n", ph->id);
	ph->state = 'E';
}

void	*routine(void *ph_struct)
{
	t_ph	*ph;
	
	ph = (t_ph *)ph_struct;
	ph->ready = 1;
	wait_the_others(ph);
	while (1)
	{           
		// usleep(10);
		if (ph->state != 'T')
			thinks(ph);
		raise_forks(ph);
		eats(ph);	
		sleeps(ph);
	}
	return (NULL);
}
