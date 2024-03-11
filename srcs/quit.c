/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:06:35 by cesar             #+#    #+#             */
/*   Updated: 2024/03/11 15:45:16 by cefuente         ###   ########.fr       */
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
	ph->table->i = 0;
	while (ph->table->i < ph->table->num_ph)
	{
		pthread_join(ph->table->threads[ph->table->i], NULL);
		pthread_join(ph->table->famine_threads[ph->table->i], NULL);
		ph->table->i++;
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