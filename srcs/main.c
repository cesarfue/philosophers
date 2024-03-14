/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:25:11 by cesar             #+#    #+#             */
/*   Updated: 2024/03/14 12:25:38 by cesar            ###   ########.fr       */
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
		ph[i]->ready = 0;
		ph[i]->table = table;
		ph[i]->state = 'S';
		ph[i]->time_since_last_meal = 0;
		define_hand(ph[i], table->num_ph);
		pthread_mutex_init(&table->forks_mut[i], NULL);
		pthread_mutex_init(&ph[i]->time_since_last_meal_mut, NULL);
		i++;
	}
	return (NULL);
}

int	init_table(char **argv, t_table *table, t_ph **ph)
{
	pthread_mutex_init(&table->famine_mut, NULL);
	pthread_mutex_init(&table->ready_mut, NULL);
	pthread_mutex_lock(&table->ready_mut);

	table->famine = 0;
	table->TTD = atoi(argv[2]);
	table->TTE = atoi(argv[3]);
	table->TTS = atoi(argv[4]);
	table->ready = 0;
	table->ph = (void **)ph;
	return (0);
}

int	main(int argc, char **argv)
{
	t_table			table;
	t_ph			**ph;
	size_t				i;

	if (argc < 2)
		return (-1);
	i = 0;
	ph = NULL;
	table.num_ph = atoi(argv[1]);
	malloc_ph(&ph, table.num_ph);
	malloc_table(table.num_ph, &table);
	init_table(argv, &table, ph);
	init_ph((int)table.num_ph, ph, &table);
	i = 0;
	while (i < table.num_ph)
	{
		pthread_create(&table.threads[i], NULL, &routine, (void *)ph[i]);
		pthread_create(&table.famine_threads[i], NULL, &famine, (void *)ph[i]);
		if (i == table.num_ph - 1)
			pthread_mutex_unlock(&table.ready_mut);
		usleep(500);
		i++;
	}
	i = 0;
	while (i < table.num_ph)
	{
		pthread_join(table.threads[i], NULL);
		pthread_join(table.famine_threads[i], NULL);
		i++;
	}
	quit_app(&table);
	return (0);
}
