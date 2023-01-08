/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 12:40:24 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/08 14:46:56 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_death(t_game *game)
{
	size_t	i;

	i = 0;
	while (i < game->number_philo)
	{
		usleep(100);
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
			return (true);
		}
		pthread_mutex_unlock(&game->eat_mutex);
		pthread_mutex_unlock(&game->dead_mutex);
		i++;
	}
	return (false);
}

bool	check_done_eating(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < game->number_philo)
	{
		usleep(100);
		pthread_mutex_lock(&game->eat_mutex);
		if (game->philo[i].done_eating_all == true)
			j++;
		if (j == game->number_philo)
		{
			game->all_philo_done_eating = true;
			pthread_mutex_unlock(&game->eat_mutex);
			return (true);
		}
		pthread_mutex_unlock(&game->eat_mutex);
		i++;
	}
	return (false);
}

/* Function for a separate thread to check if a philo is dead or is done     *
 * eating all his meals                                                      */

void	*manage_philo(void *game_cast)
{
	t_game	*game;

	game = (t_game *)game_cast;
	while (1)
	{
		if (check_death(game))
			return (NULL);
		if (check_done_eating(game))
			return (NULL);
	}
}
