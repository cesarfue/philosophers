/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:25:11 by cesar             #+#    #+#             */
/*   Updated: 2024/03/19 15:00:49 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*init_ph(int num_ph, t_ph **ph, t_table *table)
{
	int i;

	i = 0;
	while (i < num_ph)
	{
		ph[i]->id = i + 1;
		ph[i]->index = i;
		ph[i]->TTD = table->TTD;
		ph[i]->TTE = table->TTE;
		ph[i]->TTS = table->TTS;
		table->forks[i] = 0;
		ph[i]->table = table;
		ph[i]->state = 'S';
		ph[i]->time_since_last_meal = 0;
		define_hand(ph[i], table->num_ph);
		pthread_mutex_init(&table->forks_mut[i], NULL);
		pthread_mutex_init(&ph[i]->time_since_last_meal_mut, NULL);
		pthread_mutex_init(&ph[i]->starter_mut, NULL);
		pthread_mutex_lock(&ph[i]->starter_mut);
		i++;
	}
	return (NULL);
}

void	init_table(char **argv, t_table *table, t_ph **ph)
{
	pthread_mutex_init(&table->famine_mut, NULL);
	pthread_mutex_init(&table->print_mut, NULL);
	table->famine = 0;
	if (atosi(argv[2], &table->TTD) == -1)
		return (quit_app(table, 1));
	if (atosi(argv[3], &table->TTE) == -1)
		return (quit_app(table, 1));
	if (atosi(argv[4], &table->TTS) == -1)
		return (quit_app(table, 1));
	if (argv[5])
	{
		if (atosi(argv[5], &table->max_meals) == -1)
			return (quit_app(table, 1));
	}
	else
		table->max_meals = 0;
	table->ready = 0;
	table->ph = (void **)ph;
}

void	unlock_mutexes(t_table *table, t_ph **ph)
{
	size_t	i;

	i = -1;
	while (++i < table->num_ph)
		pthread_mutex_unlock(&ph[i]->starter_mut);
}

void	launch_threads(t_table *table, t_ph **ph)
{
	size_t	i;

	i = -1;
	while (++i < table->num_ph)
		pthread_create(&table->threads[i], NULL, &routine, (void *)ph[i]);
	gettimeofday(&table->start_time, NULL);
	unlock_mutexes(table, ph);
	i = 0;
	while (i < table->num_ph)
	{
		pthread_join(table->threads[i], NULL);
		pthread_join(table->famine_threads[i], NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table			table;
	t_ph			**ph;

	if (argc < 2)
		return (-1);
	ph = NULL;
	if (atosi(argv[1], (int *)&table.num_ph) == -1)
		return (quit_app(&table, 1), 1);
	// table.num_ph = atoi(argv[1]);
	malloc_ph(&ph, table.num_ph);
	malloc_table((int)table.num_ph, &table);
	init_table(argv, &table, ph);
	init_ph((int)table.num_ph, ph, &table);
	launch_threads(&table, ph);
	quit_app(&table, 0);
	return (0);
}
