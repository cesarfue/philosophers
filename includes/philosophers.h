/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:24:53 by cesar             #+#    #+#             */
/*   Updated: 2024/03/09 17:39:46 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "pthread.h"

typedef struct s_ph
{
	size_t		id;
	char	state;
	int		first_fork;
	int		second_fork;
	int		TTD;
	int		TTE;
	int		TTS;
} t_ph;

typedef struct s_table
{
	t_ph			*ph;
	pthread_t		*threads;
	pthread_t		*famine_threads;
	int				*forks;
	pthread_mutex_t	*forks_mut;
	size_t			num_ph;
	size_t			i;
	int				TTD;
	int				TTE;
	int				TTS;
	int				max_meals;
	int				ready;
} t_table;

void	quit_app(t_table *table);


#endif 