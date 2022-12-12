/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:09:40 by ltruchel          #+#    #+#             */
/*   Updated: 2022/12/12 14:38:58 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_time_start(t_game *game)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	game->time_start = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
//  This is to get time since game started
//	gettimeofday(&tv, NULL);
//	(*game)->actual_time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 - (*game)->time_start;
}
