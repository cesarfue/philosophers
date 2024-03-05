/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesar <cesar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:25:11 by cesar             #+#    #+#             */
/*   Updated: 2024/03/05 14:59:58 by cesar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	action(void)
{
	printf("ih");
}

int	main(int argc, char **argv)
{
	int num;
	int	TTD;
	int	TTE;
	int TTS;
	int i;
	pthread_mutex_t mutex;

	i = 0;
	if (argc < 5 || argc > 6)
		return (-1);
	num = atoi(argv[1]);
	pthread_t th[num];
	pthread_mutex_init(&mutex, NULL);

	while (i < num)
	{
		pthread_create(th[i], NULL, &action, NULL);
	}
	i = 0;
	while (i < num)
	{
		pthread_join(th[i], NULL);
	}

}