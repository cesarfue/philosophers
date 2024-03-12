/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:06:35 by cesar             #+#    #+#             */
/*   Updated: 2024/03/12 09:34:02 by cesar            ###   ########.fr       */
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

void	quit_app(t_ph *ph)
{
	int	i;

	i = 0;
	while (i < (int)ph->table->num_ph)
	{
		pthread_join(ph->table->threads[i], NULL);
		pthread_join(ph->table->famine_threads[i], NULL);
		i++;
	}
	if (ph->table->forks)
		free(ph->table->forks);
	// if (ph->table->forks_mut)
	// {
	// 	freetab((void *)ph->table->forks_mut, ph->table->num_ph);
	// }
	if (ph->table->threads)
		free(ph->table->threads);
	if (ph->table->famine_threads)
		free(ph->table->famine_threads);
	if (ph)
		free(ph);
	exit(0);
}