/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cefuente <cefuente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:24:53 by cesar             #+#    #+#             */
/*   Updated: 2024/03/19 17:24:19 by cefuente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "pthread.h"
# include "sys/time.h"
# include "limits.h"

typedef enum states
{
	THINKS,
	EATS,
	SLEEPS,
	RAISES_FORK,
	DEAD,
}	t_state;

typedef struct s_proxi
{
	pthread_mutex_t	*first_fork_mut;
	pthread_mutex_t	*second_fork_mut;
	pthread_mutex_t	print_mut;
}	t_proxy;

typedef struct s_table
{
	void			**ph;
	pthread_t		*threads;
	pthread_t		*famine_threads;
	int				*forks;
	pthread_mutex_t	*forks_mut;
	int				famine;
	pthread_mutex_t	famine_mut;
	pthread_mutex_t	print_mut;
	size_t			num_ph;
	size_t			i;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	size_t			ready;
	struct timeval	start_time;
}	t_table;

typedef struct s_ph
{
	size_t			id;
	size_t			index;
	int				ready;
	t_state			state;
	long			time_since_last_meal;
	pthread_mutex_t	time_since_last_meal_mut;
	pthread_mutex_t	starter_mut;
	int				first_fork;
	int				second_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals;
	t_table			*table;
}	t_ph;

int		atosi(const char *str, int *ret);
void	quit_app(t_table *table, int err);
void	wait_to_start(t_ph *ph);
void	define_hand(t_ph *ph, int num_ph);
int		malloc_table(int num_ph, t_table *table);
int		malloc_ph(t_ph ***ph, size_t num_ph);
void	*famine(void *ph_struct);
int		check_death(t_ph *ph);
int		action(t_ph *ph, long end);
int		yousleep(t_ph *ph, float ms);
int		sleeps(t_ph *ph, pthread_mutex_t print_mut);
int		eats(t_ph *ph, pthread_mutex_t print_mut);
int		thinks(t_ph *ph, pthread_mutex_t print_mut);
int		raise_forks(t_ph *ph, pthread_mutex_t *first_fork_mut,
			pthread_mutex_t *second_fork_mut, pthread_mutex_t print_mut);
void	*routine(void *ph_struct);
int		check_meals(t_ph *ph, pthread_mutex_t print_mut);
void	*death(t_ph *ph, pthread_mutex_t print_mut);
void	print_death(t_ph *ph, pthread_mutex_t print_mut);
int		print_think(t_ph *ph, pthread_mutex_t print_mut);
int		print_eat(t_ph *ph, pthread_mutex_t print_mut);
int		print_sleep(t_ph *ph, pthread_mutex_t print_mut);
int		print_fork(t_ph *ph, pthread_mutex_t print_mut);

#endif 