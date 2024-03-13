/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:49:17 by cesar             #+#    #+#             */
/*   Updated: 2024/03/13 14:29:50 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


int	action(t_ph *ph, int end, int factor)
{
	int	time;

	time = 0;
	while ((time * factor) <= (end * factor))
	{
		if (is_dead(ph) == 1)
			return (-1);
		usleep(2);
		time += 2;
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
	if (action(ph, ph->TTE, 1000) == -1)
		return (-1);
	ph->table->forks[ph->first_fork] = 0;
	pthread_mutex_unlock(&ph->table->forks_mut[ph->first_fork]);
	ph->table->forks[ph->second_fork] = 0;
	pthread_mutex_unlock(&ph->table->forks_mut[ph->second_fork]);
	return (0);
}

void	thinks(t_ph *ph)
{
	ph->state = 'T';
	printf("Philosopher %ld is thinking\n", ph->id);
}

int	raise_forks(t_ph *ph)
{
	pthread_mutex_lock(&ph->table->forks_mut[ph->first_fork]);
	if (is_dead(ph) == 1)
		return (-1) ;
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
	wait_the_others(ph, 1);
	while (1)
	{           
		if (ph->state != 'T')
			thinks(ph);
		if (raise_forks(ph) == -1)
		{
			printf("%ld exited\n", ph->id);
			return (NULL);
		}
		if (eats(ph) == -1)
		{
			printf("%ld exited\n", ph->id);
			return (NULL);
		}
		if (sleeps(ph) == -1)
		{
			printf("%ld exited\n", ph->id);
			return (NULL);
		}
	}
	return (NULL);
}
