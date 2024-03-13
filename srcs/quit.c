/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:06:35 by cesar             #+#    #+#             */
/*   Updated: 2024/03/13 14:33:51 by cesar            ###   ########.fr       */
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

void	quit_app(t_table *table)
{
	// usleep(1000);
	if (table->forks)
		free(table->forks);
	if (table->forks_mut)
		freemut(table->forks_mut, table->num_ph);
	if (table->threads)
		free(table->threads);
	if (table->famine_threads)
		free(table->famine_threads);
	pthread_mutex_destroy(&table->famine_mut);
	if (table->ph)
		freetab(table->ph, table->num_ph);
	// if (table)
	// 	free(table);
}