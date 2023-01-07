/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:11:22 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/07 16:25:36 by ltruchel         ###   ########.fr       */
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
