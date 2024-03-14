/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:24:53 by cesar             #+#    #+#             */
/*   Updated: 2024/03/14 16:12:07 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "pthread.h"
# include "sys/time.h"

typedef enum
{
	THINKS,
	EATS,
	SLEEPS,
	RAISES_FORK,
	DEAD,
} t_state;

typedef struct s_table
{
	void			**ph;
	pthread_t		*threads;
	pthread_t		*famine_threads;
	int				*forks;
	pthread_mutex_t	*forks_mut;
	int				famine;
	pthread_mutex_t	famine_mut;
	size_t			num_ph;
	size_t			i;
	float			TTD;
	int				TTE;
	int				TTS;
	int				max_meals;
	size_t			ready;
	pthread_mutex_t	ready_mut;
	struct timeval	start_time;
} t_table;

typedef struct s_ph
{
	size_t	id;
	size_t	index;
	int		ready;
	t_state	state;
	float		time_since_last_meal;
	pthread_mutex_t 	time_since_last_meal_mut;
	int		first_fork;
	int		second_fork;
	int		TTD;
	int		TTE;
	int		TTS;
	t_table	*table;
} t_ph;

void	quit_app(t_table *table);
void	wait_to_start(t_ph *ph);
void	wait_to_end(t_ph *ph);
void	define_hand(t_ph *ph, int num_ph);
void	*malloc_table(int num_ph, t_table *table);
int		malloc_ph(t_ph ***ph, size_t num_ph);
void	*famine(void *ph_struct);
int		is_dead(t_ph *ph);
int		action(t_ph *ph, long end);
int		sleeps(t_ph *ph);
int		eats(t_ph *ph);
int		thinks(t_ph *ph);
int		raise_forks(t_ph *ph);
void	*routine(void *ph_struct);
int		print_state(t_ph *ph);


#endif 