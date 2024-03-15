/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:49:17 by cesar             #+#    #+#             */
/*   Updated: 2024/03/15 14:52:16 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int print_state(t_ph *ph)
{
	struct timeval current_time;
	long elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = ((current_time.tv_sec - ph->table->start_time.tv_sec) * 1000) + ((current_time.tv_usec - ph->table->start_time.tv_usec) / 1000);
	pthread_mutex_lock(&ph->table->print_mut);
	if (ph->state == THINKS)
		printf("%ld %ld is thinking\n", elapsed_time, ph->id);
	else if (ph->state == EATS)
		printf("%ld %ld is eating\n", elapsed_time, ph->id);
	else if (ph->state == SLEEPS)
		printf("%ld %ld is sleeping\n", elapsed_time, ph->id);
	else if (ph->state == RAISES_FORK)
		printf("%ld %ld has raised a fork\n", elapsed_time, ph->id);
	else if (ph->state == DEAD)
		printf("%ld %ld died\n", elapsed_time, ph->id);
	pthread_mutex_unlock(&ph->table->print_mut);
	return (0);
}

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
		usleep(ph->table->num_ph * 10);
		// usleep(2);
	}
}

int sleeps(t_ph *ph)
{
	ph->state = SLEEPS;
	print_state(ph);
	if (action(ph, ph->TTS) == -1)
		return (-1);
	return (0);
}

int eats(t_ph *ph)
{
	ph->state = EATS;
	ph->meals++;
	print_state(ph);
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
	ph->state = THINKS;
	if (check_death(ph) == 1)
		return (-1);
	print_state(ph);
	// usleep(2);
	usleep(ph->table->num_ph * 10);

	return (0);
}

int raise_forks(t_ph *ph)
{
	pthread_mutex_lock(&ph->table->forks_mut[ph->first_fork]);
	if (check_death(ph) == 1)
		return (-1);
	ph->table->forks[ph->first_fork] = 1;
	ph->state = RAISES_FORK;
	print_state(ph);
	pthread_mutex_lock(&ph->table->forks_mut[ph->second_fork]);
	if (check_death(ph) == 1)
		return (-1);
	ph->table->forks[ph->second_fork] = 1;
	ph->state = RAISES_FORK;
	print_state(ph);
	return (0);
}

void *routine(void *ph_struct)
{
	t_ph *ph;

	ph = (t_ph *)ph_struct;
	wait_to_start(ph);
	pthread_mutex_lock(&ph->table->print_mut);
	printf("%ld started\n", ph->id);
	pthread_mutex_unlock(&ph->table->print_mut);

	while (1)
	{
		// if (ph->state != THINKS)
		// {
			if (thinks(ph) == -1)
				return (NULL);
		// }
		if (raise_forks(ph) == -1)
			return (NULL);
		if (eats(ph) == -1)
			return (NULL);
		if (sleeps(ph) == -1)
			return (NULL);
	}
	return (NULL);
}
