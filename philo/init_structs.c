/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:46:44 by ltruchel          #+#    #+#             */
/*   Updated: 2022/12/12 20:07:00 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_structs(t_game *game, char **av)
{
	game->number_philo = ft_atoui(av[1]);
	game->time_die = ft_atoui(av[2]);
	game->time_eat = ft_atoui(av[3]);
	game->time_sleep = ft_atoui(av[4]);
	if (av[5])
		game->must_eat = ft_atoui(av[5]);
	get_time_start(game);
	init_philos(game);
}

void	init_philos(t_game *game)
{
	size_t	i;

	game->philo = malloc(sizeof(t_philo) * game->number_philo);
	if (!game->philo)
		return ;
	i = 0;
	while (i < game->number_philo)
	{
		game->philo[i].n = i + 1;
		game->philo[i].last_meal = 0;
		game->philo[i].meal_eaten = 0;
		game->philo[i].dead = 0;
		pthread_mutex_init(&game->philo[i].r_fork, NULL);
		if (i == game->number_philo - 1)
			game->philo[i].l_fork
				= &(game->philo[game->number_philo - 1].r_fork);
		else
			game->philo[i].l_fork = &(game->philo[i - 1].r_fork);
		pthread_create(&game->philo[i].thread, NULL, algo_philo, &game);
		i++;
	}
}
