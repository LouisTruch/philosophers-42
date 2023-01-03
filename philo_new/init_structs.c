/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:24:42 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/03 16:58:35 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Function for a separate thread to check if a philo is dead or is done     *
 * eating all his meals                                                      */

void	*manage_philo(void *ga)
{
	size_t	i;
	size_t	j;
	t_game	*game;

	game = (t_game *)ga;
	j = 0;
	while (1)
	{
		i = 0;
		while (i < game->number_philo)
		{
			pthread_mutex_lock(&game->dead_mutex);
			pthread_mutex_lock(&game->eat_mutex);
			if (time_action() - game->philo[i].last_meal_ms
				> (long long)game->time_die)
			{
				game->dead_bool = true;
				pthread_mutex_unlock(&game->eat_mutex);
				pthread_mutex_unlock(&game->dead_mutex);
				pthread_mutex_lock(&game->print_mutex);
				printf("%s%lld %zu died \n%s",
					RED, time_action(), game->philo[i].n, NC);
				pthread_mutex_unlock(&game->print_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&game->eat_mutex);
			pthread_mutex_unlock(&game->dead_mutex);
			i++;
		}
		i = 0;
		j = 0;
		while (i < game->number_philo)
		{
			pthread_mutex_lock(&game->eat_mutex);
			if (game->philo[i].done_eating_all == true)
			{
				pthread_mutex_unlock(&game->eat_mutex);
				j++;
			}
			pthread_mutex_unlock(&game->eat_mutex);
			i++;
		}
		if (j == game->number_philo)
			return (NULL);
	}
}

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
	game->dead_bool = 0;
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
	i = 0;
	while (i < game->number_philo)
	{
		game->philo[i].n = i + 1;
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
//		printf("%zu l= %p  r= %p\n", i + 1, game->philo[i].l_fork, game->philo[i].r_fork);
		pthread_create(&game->philo[i].thread,
			NULL, start_philo, &game->philo[i]);
		i++;
	}
	i = 0;
	usleep(1000);
	pthread_create(&game->manager_philo, NULL, manage_philo, game);
	while (i < game->number_philo)
	{
		pthread_join(game->philo[i].thread, NULL);
		i++;
	}
	pthread_join(game->manager_philo, NULL);
	free (game->philo);
}
