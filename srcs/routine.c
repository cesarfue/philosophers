/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:49:17 by cesar             #+#    #+#             */
/*   Updated: 2024/03/18 10:35:59 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int sleeps(t_ph *ph)
{
	if (print_sleep(ph) == -1)
		return (-1);
	if (action(ph, ph->TTS) == -1)
		return (-1);
	return (0);
}

int eats(t_ph *ph)
{
	ph->meals++;
	if (print_eat(ph) == -1)
		return (-1);
	if (action(ph, ph->TTE) == -1)
		return (-1);
	if (check_meals(ph) == -1)
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

int thinks(t_ph *ph)
{
	if (print_think(ph) == -1)
		return (-1);
	return (0);
}

int raise_forks(t_ph *ph, pthread_mutex_t first_fork_mut, pthread_mutex_t second_fork_mut)
{
	// pthread_mutex_lock(&first_fork_mut);
	// ph->table->forks[ph->first_fork] = 1;
	// if (print_fork(ph) == -1)
	// 	return (-1);
	// pthread_mutex_lock(&second_fork_mut);
	// ph->table->forks[ph->second_fork] = 1;
	// if (print_fork(ph) == -1)
	// 	return (-1);
	pthread_mutex_lock(&first_fork_mut);
	if (ph->table->forks[ph->first_fork] == 0)
	{
		ph->table->forks[ph->first_fork] = 1;
		if (print_fork(ph) == -1)
			return (-1);
		pthread_mutex_lock(&second_fork_mut);
		if (ph->table->forks[ph->second_fork] == 0)
		{
			ph->table->forks[ph->second_fork] = 1;
			if (print_fork(ph) == -1)
				return (-1);
		}
		pthread_mutex_unlock(&second_fork_mut);
	}
	pthread_mutex_unlock(&first_fork_mut);
	return (0);
}

void *routine(void *ph_struct)
{
	t_ph *ph;
	pthread_mutex_t	first_fork_mut;
	pthread_mutex_t	second_fork_mut;

	ph = (t_ph *)ph_struct;
	first_fork_mut = ph->table->forks_mut[ph->first_fork];
	second_fork_mut = ph->table->forks_mut[ph->second_fork];
	wait_to_start(ph);
	pthread_create(&ph->table->famine_threads[ph->index], NULL, &famine, (void *)ph);
	// if (ph->index % 2 != 0)
	// 	usleep(ph->table->num_ph * 1000);
	while (1)
	{
		if (thinks(ph) == -1)
			return (NULL);
		if (raise_forks(ph, first_fork_mut, second_fork_mut) == -1)
			return (NULL);
		if (eats(ph) == -1)
			return (NULL);
		if (sleeps(ph) == -1)
			return (NULL);
		usleep(ph->table->num_ph * 10);
	}
	return (NULL);
}
