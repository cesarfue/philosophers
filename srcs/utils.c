/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:05:10 by cefuente          #+#    #+#             */
/*   Updated: 2024/03/11 16:09:33 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_ready(t_ph *ph)
{
	size_t	i; 

	i = 0;
	while (i < ph->table->num_ph)
	{
		if (((t_ph *)(ph->table->ph[i]))->ready == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}
void	wait_the_others(t_ph *ph)
{
	while (check_ready(ph) == 0)
	{
		usleep(10);
	}
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

void	*malloc_table(int num_ph, t_ph **ph, t_table *table)
{
	*ph = malloc(num_ph * sizeof(t_ph));
	if (!(*ph))
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
	return (NULL);
}