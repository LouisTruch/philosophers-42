/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:11:22 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/08 15:42:57 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Timestamp function, first time it is called set initial_time              *
 * Then return the elapsed time since the function was first called (in ms)  */

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
		sem_wait(philo->game->sem_eat);
		if (philo->is_dead == true)
		{
			sem_post(philo->game->sem_eat);
			break ;
		}
		sem_post(philo->game->sem_eat);
	}
}
