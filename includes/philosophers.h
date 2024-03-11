/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:24:53 by cesar             #+#    #+#             */
/*   Updated: 2024/03/11 15:53:41 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "pthread.h"

typedef struct s_table
{
	void			**ph;
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

typedef struct s_ph
{
	size_t		id;
	int		ready;
	char	state;
	int		first_fork;
	int		second_fork;
	int		TTD;
	int		TTE;
	int		TTS;
	t_table	*table;
} t_ph;


void	quit_app(t_ph *ph);
int		check_ready(t_ph *ph);
void	wait_the_others(t_ph *ph);
void	define_hand(t_ph *ph, int num_ph);
void	*malloc_table(int num_ph, t_ph **ph, t_table *table);


#endif 