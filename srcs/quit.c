/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:06:35 by cesar             #+#    #+#             */
/*   Updated: 2024/03/19 12:30:05 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	freemut(pthread_mutex_t *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&tab[i++]);
	}
	free(tab);
}

void	freetab(void **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
}

void	freetabmut(void **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&((t_ph **)tab)[i++]->time_since_last_meal_mut);
	}
}

void	quit_app(t_table *table, int err)
{
	if (table->forks)
		free(table->forks);
	if (table->forks_mut)
		freemut(table->forks_mut, table->num_ph);
	if (table->threads)
		free(table->threads); 
	if (table->famine_threads)
		free(table->famine_threads);
	pthread_mutex_destroy(&table->famine_mut);
	freetabmut(table->ph, table->num_ph);
	if (table->ph)
		freetab(table->ph, table->num_ph);
	if (table)
		free(table);
	if (err != 0)
		printf("Error\n");
	return ;
}