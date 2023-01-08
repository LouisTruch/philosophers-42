/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:11:22 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/08 15:23:55 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_action(void)
{
	struct timeval		tv;
	static long long	initial_time;
	static bool			bool_time;
	long long			time;

	if (bool_time == false)
	{
		gettimeofday(&tv, NULL);
		initial_time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
		bool_time = true;
		return (0);
	}
	else
	{	
		gettimeofday(&tv, NULL);
		time = ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - initial_time;
	}
	return (time);
}

/* Sequenced usleep to avoid philo from doing their action                    *
 * if simulation is over                                                     */

void	ft_usleep(t_philo *philo, size_t time)
{
	size_t		i;
	long long	start_time;
	long long	start_time_buffer;

	i = 0;
	start_time = time_action();
	start_time_buffer = start_time + time;
	while (start_time <= start_time_buffer)
	{
		usleep(500);
		start_time = time_action();
		pthread_mutex_lock(&philo->game->dead_mutex);
		pthread_mutex_lock(&philo->game->eat_mutex);
		if (philo->game->dead_bool == true
			|| philo->game->all_philo_done_eating == true)
		{
			pthread_mutex_unlock(&philo->game->eat_mutex);
			pthread_mutex_unlock(&philo->game->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->game->eat_mutex);
		pthread_mutex_unlock(&philo->game->dead_mutex);
	}
}
