/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:49:17 by cesar             #+#    #+#             */
/*   Updated: 2024/03/14 17:31:36 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	print_state(t_ph *ph)
{
	struct timeval	current_time;
	long			elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = ((current_time.tv_sec - ph->table->start_time.tv_sec) * 1000)
		 + ((current_time.tv_usec - ph->table->start_time.tv_usec) / 1000);
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
	return (0);
}

int	action(t_ph *ph, long end)
{
	struct timeval	time;
	long			start_time;
	long			current_time;
	long			end_time;

	gettimeofday(&time, NULL);
	start_time = ((time.tv_sec - ph->table->start_time.tv_sec) * 1000) + ((time.tv_usec - ph->table->start_time.tv_usec) / 1000);
	end_time = start_time + end;
	printf("start_time : %ld, end time : %ld\n", start_time, end_time);
	while (1)
	{
		if (is_dead(ph) == 1)
			return (-1);
		gettimeofday(&time, NULL);
		current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
		printf("elapsed time %ld\n", current_time);
		usleep(5);
		if (current_time >= end_time)
			return (0); 
	}
}

// int	action(t_ph *ph, int end, int factor)
// {
// 	long	time;

// 	time = 0;
// 	while ((time) <= (long)(end * factor))
// 	{
// 		if (is_dead(ph) == 1)
// 			return (-1);
// 		usleep(50);
// 		time += 50;
// 	}
// 	return (0);
// }

int	sleeps(t_ph *ph)
{
	ph->state = SLEEPS;
	if (print_state(ph) == -1)
		return (-1);
	if (action(ph, ph->TTS) == -1)
		return (-1);
	return (0);
}

int	eats(t_ph *ph)
{
	ph->state = EATS;
	if (print_state(ph) == -1)
		return (-1);
	pthread_mutex_lock(&ph->time_since_last_meal_mut);
	ph->time_since_last_meal = 0;
	pthread_mutex_unlock(&ph->time_since_last_meal_mut);
	if (action(ph, ph->TTE) == -1)
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
	ph->state = THINKS;
	if (print_state(ph) == -1)
		return (-1);
	usleep(500);
	return (0);
}

int	raise_forks(t_ph *ph)
{
	pthread_mutex_lock(&ph->table->forks_mut[ph->first_fork]);
	if (is_dead(ph) == 1)
			return (-1);
	ph->table->forks[ph->first_fork] = 1;
	ph->state = RAISES_FORK;
	if (print_state(ph) == -1)
		return (-1);
	pthread_mutex_lock(&ph->table->forks_mut[ph->second_fork]);
	if (is_dead(ph) == 1)
			return (-1);
	ph->table->forks[ph->second_fork] = 1;
	if (print_state(ph) == -1)
		return (-1);
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
