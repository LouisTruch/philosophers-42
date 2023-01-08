/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:24:42 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/08 12:40:51 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Function to initialise game struct                                         */

void	init_struct(t_game *game, char **av)
{
	game->number_philo = ft_atoui(av[1]);
	game->time_die = ft_atoui(av[2]);
	game->time_eat = ft_atoui(av[3]);
	game->time_sleep = ft_atoui(av[4]);
	if (av[5])
		game->must_eat = ft_atoui(av[5]);
	else
		game->must_eat = 0;
	time_action();
	game->dead_bool = false;
	game->all_philo_done_eating = false;
	pthread_mutex_init(&game->print_mutex, NULL);
	pthread_mutex_init(&game->dead_mutex, NULL);
	pthread_mutex_init(&game->eat_mutex, NULL);
	init_philo(game);
}

/* Function to initialise every philo, and to start every thread              */

void	init_philo(t_game *game)
{
	size_t	i;

	game->philo = malloc(sizeof(t_philo) * game->number_philo);
	if (!game->philo)
		return ;
	i = -1;
	while (++i < game->number_philo)
	{
		game->philo[i].n = i + 1;
		game->philo[i].l_fork = NULL;
		game->philo[i].last_meal_ms = 0;
		game->philo[i].total_meal_eaten = 0;
		game->philo[i].done_eating_all = false;
		game->philo[i].game = game;
		pthread_mutex_init(&game->philo[i].r_fork, NULL);
		if (i == 0)
			game->philo[i].l_fork
				= &game->philo[game->number_philo - 1].r_fork;
		else
			game->philo[i].l_fork = &game->philo[i - 1].r_fork;
		pthread_create(&game->philo[i].thread,
			NULL, start_philo, &game->philo[i]);
	}
	pthread_create(&game->manager_philo, NULL, manage_philo, game);
	join_threads(game);
}

void	join_threads(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->number_philo)
	{
		pthread_join(game->philo[i].thread, NULL);
		i++;
	}
	pthread_join(game->manager_philo, NULL);
	ft_free(game);
}
