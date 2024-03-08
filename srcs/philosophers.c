/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:25:11 by cesar             #+#    #+#             */
/*   Updated: 2024/03/08 16:54:56 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	sleeps(t_ph *ph)
{
	ph->state = 'S';
	printf("Philosopher %ld is sleeping\n", ph->id);
	usleep(ph->TTS * 1000);
	printf("Philosopher %ld has finished sleeping\n", ph->id);
}

void	eats(t_ph *ph, t_table *table)
{
	printf("Philosopher %ld is eating\n", ph->id);
	usleep(ph->TTE * 1000);
	table->forks[ph->first_fork] = 0;
	pthread_mutex_unlock(&table->forks_mut[ph->first_fork]);
	table->forks[ph->second_fork] = 0;
	pthread_mutex_unlock(&table->forks_mut[ph->second_fork]);
	printf("Philosopher %ld has finished eating\n", ph->id);
}

void	thinks(t_ph *ph)
{
	ph->state = 'T';
	printf("Philosopher %ld is thinking\n", ph->id);
}


void	raise_forks(t_ph *ph, t_table *table)
{
	pthread_mutex_lock(&table->forks_mut[ph->first_fork]);
	ph->state = 'H';
	table->forks[ph->first_fork] = 1;
	printf("Philosopher %ld has raised a fork\n", ph->id);
	pthread_mutex_lock(&table->forks_mut[ph->second_fork]);
	table->forks[ph->second_fork] = 1;
	printf("Philosopher %ld has raised a fork\n", ph->id);
	ph->state = 'E';
}

void	wait_the_others(t_table *table)
{
	while (1)
	{
		if (table->ready == 1)
		{
			printf("ready\n");
			break;
		}
		usleep(1);
	}
}
void	*routine(void *table_struct)
{
	t_table *table;
	t_ph	*ph;
	
	table = (t_table *)table_struct;
	ph = &table->ph[table->i];
	// if (ph->id == table->num_ph)
	// {
	// 	table->ready = 1;
	// 	usleep(100);
	// }
	// else
	// 	wait_the_others(table);
	while (1)
	{
		if (ph->state != 'T')
			thinks(ph);
		raise_forks(ph, table);
		eats(ph, table);	
		sleeps(ph);
	}
	return (NULL);
}


void	*famine(void *table_struct)
{
	t_table	*table;
	t_ph	*ph;

	table = (t_table *)table_struct;
	ph = &table->ph[table->i];
	// wait_the_others(table);
	usleep(ph->TTD * 1000);
	if (ph->state != 'E')
	{
		ph->state = 'D'; 
		printf("Philosopher %ld has died\n", ph->id);
		exit(0);
	}
	return (NULL);
}

void	define_hand(t_ph *ph, int num_ph)
{
	if (ph->id % 2 == 0)
	{
		ph->first_fork = ((ph->id + 1) % num_ph);
		ph->second_fork = ph->id % num_ph;
	}
	else
	{
		ph->first_fork = ph->id % num_ph;
		ph->second_fork = ((ph->id + 1) % num_ph);
	}
}

void	*init_table(int num_ph, t_table *table)
{
	int i;

	i = 0;
	table->ph = malloc(num_ph * sizeof(t_ph));
	if (!(table->ph))
		return (NULL);
	table->forks = malloc(num_ph * sizeof(int));
	if (!(table->forks))
		return (NULL);
	table->forks_mut = malloc(num_ph * sizeof(pthread_mutex_t));
	if (!(table->forks_mut))
		return (NULL);
	table->threads = malloc(num_ph * sizeof(pthread_t));
	if (!(table->threads))
		return (NULL);
	table->famine_threads = malloc(num_ph * sizeof(pthread_t));
	if (!(table->famine_threads))
		return (NULL);
	while (i < num_ph)
	{
		table->ph[i].id = i + 1;
		table->ph[i].TTD = table->TTD;
		table->ph[i].TTE = table->TTE;
		table->ph[i].TTS = table->TTS;
		table->forks[i] = 0;
		define_hand(&table->ph[i], table->num_ph);
		pthread_mutex_init(&table->forks_mut[i], NULL);
		i++;
	}
	return (NULL);
}



int	main(int argc, char **argv)
{
	t_table			table;

	if (argc < 2)
		return (-1);
	table.i = 0;
	table.num_ph = atoi(argv[1]);
	table.TTD = atoi(argv[2]);
	table.TTE = atoi(argv[3]);
	table.TTS = atoi(argv[4]);
	table.ready = 0;
	init_table((int)table.num_ph, &table);
	while (table.i < table.num_ph)
	{
		pthread_create(&table.threads[table.i], NULL, &routine, (void *)&table);
		pthread_create(&table.famine_threads[table.i], NULL, &famine, (void *)&table);
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
