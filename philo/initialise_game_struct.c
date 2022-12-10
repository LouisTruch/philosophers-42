/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_game_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:46:44 by ltruchel          #+#    #+#             */
/*   Updated: 2022/12/10 19:06:57 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialise_structs(t_game *game, char **av)
{
	game->n = ft_atoui(av[1]);
	game->time_die = ft_atoui(av[2]);
	game->time_eat = ft_atoui(av[3]);
	game->time_sleep = ft_atoui(av[4]);
	if (av[5])
		game->must_eat = ft_atoui(av[5]);
	get_time_start(&game);
	initialise_philos(&game);
}

void	get_time_start(t_game **game)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	(*game)->time_start = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	usleep(1000);
//  This is to get time since game started
//	gettimeofday(&tv, NULL);
//	(*game)->actual_time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000 - (*game)->time_start;
}

void	initialise_philos(t_game **game)
{

}
