/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:25:11 by cesar             #+#    #+#             */
/*   Updated: 2024/03/11 16:21:47 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_dead(t_ph *ph)
{
	if (ph->state == 'D')
		return (quit_app(ph), 1);
	return (0);

}

void	sleeps(t_ph *ph)
{
	ph->state = 'S';
	printf("Philosopher %ld is sleeping\n", ph->id);
	usleep(ph->TTS * 1000);
}

void	eats(t_ph *ph)
{
	printf("Philosopher %ld is eating\n", ph->id);
	usleep(ph->TTE * 1000);
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
	ph->state = 'H';
	ph->table->forks[ph->first_fork] = 1;
	printf("Philosopher %ld has raised a fork\n", ph->id);
	while (!is_dead(ph) && pthread_mutex_lock(&ph->table->forks_mut[ph->second_fork]) != 0)
		usleep(1);
	ph->table->forks[ph->second_fork] = 1;
	printf("Philosopher %ld has raised a fork\n", ph->id);
	ph->state = 'E';
}

void	*routine(void *ph_struct)
{
	t_ph	*ph;
	
	ph = (t_ph *)ph_struct;
	ph->ready = 1;
	// wait_the_others(ph);
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

void	*famine(void *ph_struct)
{
	t_ph	*ph;

	ph = (t_ph *)ph_struct;
	// wait_the_others(ph);
	usleep(ph->TTD * 1000);
	if (ph->state != 'E')
	{
		printf("Philosopher %ld(%c) has died\n", ph->id, ph->state);
		ph->state = 'D'; 
		quit_app(ph);
	}
	return (NULL);
}

void	*init_ph(int num_ph, t_ph **ph, t_table *table)
{
	int i;

	i = 0;
	while (i < num_ph)
	{
		ph[i]->id = i + 1;
		ph[i]->TTD = table->TTD;
		ph[i]->TTE = table->TTE;
		ph[i]->TTS = table->TTS;
		table->forks[i] = 0;
		ph[i]->ready = 0;
		ph[i]->table = table;
		define_hand(ph[i], table->num_ph);
		pthread_mutex_init(&table->forks_mut[i], NULL);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_table			table;
	t_ph			*ph;

	if (argc < 2)
		return (-1);
	table.i = 0;
	table.num_ph = atoi(argv[1]);
	table.TTD = atoi(argv[2]);
	table.TTE = atoi(argv[3]);
	table.TTS = atoi(argv[4]);
	table.ready = 0;
	table.ph = (void **)&ph;
	malloc_table((int)table.num_ph, &ph, &table);
	init_ph((int)table.num_ph, &ph, &table);
	while (table.i < table.num_ph)
	{
		pthread_create(&table.threads[table.i], NULL, &routine, (void *)&ph[table.i]);
		pthread_create(&table.famine_threads[table.i], NULL, &famine, (void *)&ph[table.i]);
		usleep(500);
		table.i++;
	}
	table.i = 0;
	while (table.i < table.num_ph)
	{
		pthread_join(table.threads[table.i], NULL);
		pthread_join(table.famine_threads[table.i], NULL);
		table.i++;
	}
	return (0);
}
