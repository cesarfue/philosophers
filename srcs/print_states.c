/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:33:17 by cesar             #+#    #+#             */
/*   Updated: 2024/03/16 18:22:17 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_death(t_ph *ph)
{
	struct timeval current_time;
	long elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = ((current_time.tv_sec - ph->table->start_time.tv_sec) * 1000) + ((current_time.tv_usec - ph->table->start_time.tv_usec) / 1000);
	pthread_mutex_lock(&ph->table->print_mut);	
	printf("%ld %ld died\n", elapsed_time, ph->id);
	pthread_mutex_unlock(&ph->table->print_mut);
}

int	print_think(t_ph *ph)
{
	struct timeval current_time;
	long elapsed_time;

	if (check_death(ph) == 1)
		return (-1);
	gettimeofday(&current_time, NULL);
	elapsed_time = ((current_time.tv_sec - ph->table->start_time.tv_sec) * 1000) + ((current_time.tv_usec - ph->table->start_time.tv_usec) / 1000);
	pthread_mutex_lock(&ph->table->print_mut);	
	printf("%ld %ld is thinking\n", elapsed_time, ph->id);
	pthread_mutex_unlock(&ph->table->print_mut);
	return (0);
}

int	print_eat(t_ph *ph)
{
	struct timeval current_time;
	long elapsed_time;

	if (check_death(ph) == 1)
		return (-1);
	gettimeofday(&current_time, NULL);
	elapsed_time = ((current_time.tv_sec - ph->table->start_time.tv_sec) * 1000) + ((current_time.tv_usec - ph->table->start_time.tv_usec) / 1000);
	pthread_mutex_lock(&ph->table->print_mut);	
	printf("%ld %ld is eating\n", elapsed_time, ph->id);
	pthread_mutex_unlock(&ph->table->print_mut);
	return (0);
}

int	print_sleep(t_ph *ph)
{
	struct timeval current_time;
	long elapsed_time;

	if (check_death(ph) == 1)
		return (-1);
	gettimeofday(&current_time, NULL);
	elapsed_time = ((current_time.tv_sec - ph->table->start_time.tv_sec) * 1000) + ((current_time.tv_usec - ph->table->start_time.tv_usec) / 1000);
	pthread_mutex_lock(&ph->table->print_mut);	
	printf("%ld %ld is sleeping\n", elapsed_time, ph->id);
	pthread_mutex_unlock(&ph->table->print_mut);
	return (0);
}

int	print_fork(t_ph *ph)
{
	struct timeval current_time;
	long elapsed_time;

	if (check_death(ph) == 1)
		return (-1);
	gettimeofday(&current_time, NULL);
	elapsed_time = ((current_time.tv_sec - ph->table->start_time.tv_sec) * 1000) + ((current_time.tv_usec - ph->table->start_time.tv_usec) / 1000);
	pthread_mutex_lock(&ph->table->print_mut);	
	printf("%ld %ld has raised a fork\n", elapsed_time, ph->id);
	pthread_mutex_unlock(&ph->table->print_mut);
	return (0);
}

