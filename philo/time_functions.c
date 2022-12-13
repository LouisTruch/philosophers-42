/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:09:40 by ltruchel          #+#    #+#             */
/*   Updated: 2022/12/13 15:09:45 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_action(void)
{
	struct timeval		tv;
	static long long	initial_time;
	static bool			bool_time = 0;
	long long			time;

	if (bool_time == 0)
	{
		gettimeofday(&tv, NULL);
		initial_time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
		bool_time = 1;
		return (0);
	}
	else
	{	
		gettimeofday(&tv, NULL);
		time = ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000) - initial_time;
	}
	return (time);
}
