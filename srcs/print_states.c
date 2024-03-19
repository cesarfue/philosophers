/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:33:17 by cesar             #+#    #+#             */
/*   Updated: 2024/03/19 17:13:50 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_death(t_ph *ph, pthread_mutex_t print_mut)
{
	struct timeval	current_time;
	long			elapsed_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = ((current_time.tv_sec - ph->table->start_time.tv_sec)
			* 1000) + ((current_time.tv_usec - ph->table->start_time.tv_usec)
			/ 1000);
	pthread_mutex_lock(&print_mut);
	printf("%ld %ld died\n", elapsed_time, ph->id);
	pthread_mutex_unlock(&print_mut);
}

int	print_think(t_ph *ph, pthread_mutex_t print_mut)
{
	struct timeval	current_time;
	long			elapsed_time;

	if (check_death(ph) == 1)
		return (-1);
	gettimeofday(&current_time, NULL);
	elapsed_time = ((current_time.tv_sec - ph->table->start_time.tv_sec)
			* 1000) + ((current_time.tv_usec - ph->table->start_time.tv_usec)
			/ 1000);
	pthread_mutex_lock(&print_mut);
	printf("%ld %ld is thinking\n", elapsed_time, ph->id);
	pthread_mutex_unlock(&print_mut);
	return (0);
}

int	print_eat(t_ph *ph, pthread_mutex_t print_mut)
{
	struct timeval	current_time;
	long			elapsed_time;

	if (check_death(ph) == 1)
		return (-1);
	gettimeofday(&current_time, NULL);
	elapsed_time = ((current_time.tv_sec - ph->table->start_time.tv_sec)
			* 1000) + ((current_time.tv_usec - ph->table->start_time.tv_usec)
			/ 1000);
	pthread_mutex_lock(&print_mut);
	printf("%ld %ld is eating\n", elapsed_time, ph->id);
	pthread_mutex_unlock(&print_mut);
	return (0);
}

int	print_sleep(t_ph *ph, pthread_mutex_t print_mut)
{
	struct timeval	current_time;
	long			elapsed_time;

	if (check_death(ph) == 1)
		return (-1);
	gettimeofday(&current_time, NULL);
	elapsed_time = ((current_time.tv_sec - ph->table->start_time.tv_sec)
			* 1000) + ((current_time.tv_usec - ph->table->start_time.tv_usec)
			/ 1000);
	pthread_mutex_lock(&print_mut);
	printf("%ld %ld is sleeping\n", elapsed_time, ph->id);
	pthread_mutex_unlock(&print_mut);
	return (0);
}

int	print_fork(t_ph *ph, pthread_mutex_t print_mut)
{
	struct timeval	current_time;
	long			elapsed_time;

	if (check_death(ph) == 1)
		return (-1);
	gettimeofday(&current_time, NULL);
	elapsed_time = ((current_time.tv_sec - ph->table->start_time.tv_sec)
			* 1000) + ((current_time.tv_usec - ph->table->start_time.tv_usec)
			/ 1000);
	pthread_mutex_lock(&print_mut);
	printf("%ld %ld has raised a fork\n", elapsed_time, ph->id);
	pthread_mutex_unlock(&print_mut);
	return (0);
}
