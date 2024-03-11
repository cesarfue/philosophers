/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:06:35 by cesar             #+#    #+#             */
/*   Updated: 2024/03/11 11:31:32 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	freetab(void **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(tab[i++]);
	}
	free(tab);
}

void	quit_app(t_table *table)
{
	while (table->i < table->num_ph)
	{
		pthread_join(table->threads[table->i], NULL);
		pthread_join(table->famine_threads[table->i], NULL);
		table->i++;
	}
	if (table->ph)
		free(table->ph);
	if (table->forks)
		free(table->forks);
	// if (table->forks_mut)
	// {
	// 	freetab((void *)table->forks_mut, table->num_ph);
	// }
	if (table->threads)
		free(table->threads);
	if (table->famine_threads)
		free(table->famine_threads);
	exit(0);
}