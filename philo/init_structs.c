/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 19:46:44 by ltruchel          #+#    #+#             */
/*   Updated: 2022/12/16 12:54:55 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*manage_philo(void *ga)
{
	size_t	i;
	size_t	j;
	t_game	*game;

	game = (t_game *)ga;
	while (1)
	{
		i = 0;
		while (i < game->number_philo)
		{
			pthread_mutex_lock(&game->dead_mutex);
			if (time_action() - game->philo[i].last_meal_ms
				> (long long)game->time_die)
			{
				pthread_mutex_unlock(&game->dead_mutex);
				pthread_mutex_lock(&game->print_mutex);
				pthread_mutex_lock(&game->dead_mutex);
				game->dead_bool = 1;
				printf("%s%lld %zu died\n%s",
					RED, time_action(), game->philo[i].n, NC);
				pthread_mutex_unlock(&game->dead_mutex);
				pthread_mutex_unlock(&game->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&game->dead_mutex);
			i++;
		}
		i = 0;
		j = 0;
		while (i < game->number_philo)
		{
			if (game->philo[i].done_must_eat == 1)
				j++;
			i++;
		}
		if (j == game->number_philo)
			return (NULL);
	}
	return (NULL);
}

void	init_structs(t_game *game, char **av)
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
	game->dead_bool = 0;
	pthread_mutex_init(&game->print_mutex, NULL);
	pthread_mutex_init(&game->dead_mutex, NULL);
	pthread_mutex_init(&game->sleep_mutex, NULL);
	pthread_mutex_init(&game->think_mutex, NULL);
	pthread_mutex_init(&game->pick_mutex, NULL);
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
		if (i == 0 || i == game->number_philo - 1)
		{
			if (i == 0)
			{
				game->philo[i].next = i + 1;
				game->philo[i].prev = game->number_philo - 1;
			}
			if (i == game->number_philo - 1)
			{
				game->philo[i].next = 0;
				game->philo[i].prev = i - 1;
			}
		}
		else
		{
			game->philo[i].next = i + 1;
			game->philo[i].prev = i - 1;
		}
		game->philo[i].last_meal_ms = 0;
		game->philo[i].total_meal_eaten = 0;
		pthread_mutex_lock(&game->pick_mutex);
		game->philo[i].eating = 0;
		pthread_mutex_unlock(&game->pick_mutex);
		game->philo[i].done_must_eat = 0;
		game->philo[i].game = game;
		pthread_mutex_init(&game->philo[i].r_fork, NULL);
		if (i == 0)
			game->philo[i].l_fork
				= &(game->philo[game->number_philo - 1].r_fork);
		else
			game->philo[i].l_fork = &(game->philo[i - 1].r_fork);
		pthread_create(&game->philo[i].thread, NULL, algo_philo, &game->philo[i]);
		i++;
	}
	pthread_create(&game->manager_philo, NULL, manage_philo, game);
	i = 0;
	while (i < game->number_philo)
	{
		pthread_join(game->philo[i].thread, NULL);
		i++;
	}
	pthread_join(game->manager_philo, NULL);
	free(game->philo);
}
