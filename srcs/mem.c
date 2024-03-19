/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:22:32 by cesar             #+#    #+#             */
/*   Updated: 2024/03/19 12:50:33 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	malloc_ph(t_ph ***ph, size_t num_ph)
{
	size_t	i;

	i = 0;
	*ph = malloc(num_ph * sizeof(t_ph *));
	if (!*ph)
		return (-1);
	while (i < num_ph)
	{
		(*ph)[i] = malloc(sizeof(t_ph));
		if(!((*ph)[i]))
			return (-1);
		i++;
	}
	return (0);
}

void	*malloc_table(int num_ph, t_table *table)
{
	table->forks = NULL;
	table->forks = malloc(num_ph * sizeof(int));
	if (!(table->forks))
		return (NULL);
	table->forks_mut = NULL;
	table->forks_mut = malloc(num_ph * sizeof(pthread_mutex_t));
	if (!(table->forks_mut))
		return (NULL);
	table->threads = NULL;
	table->threads = malloc(num_ph * sizeof(pthread_t));
	if (!(table->threads))
		return (NULL);
	table->famine_threads = NULL;
	table->famine_threads = malloc(num_ph * sizeof(pthread_t));
	if (!(table->famine_threads))
		return (NULL);
	return (NULL);
}