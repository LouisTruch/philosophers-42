/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:50:54 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/04 11:53:44 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mutex(t_philo *philo, char *color, char *str)
{
	pthread_mutex_lock(&philo->game->print_mutex);
	pthread_mutex_lock(&philo->game->dead_mutex);
	if (philo->game->dead_bool == true)
	{
		pthread_mutex_unlock(&philo->game->dead_mutex);
		pthread_mutex_unlock(&philo->game->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->game->dead_mutex);
	printf("%s%lld %zu %s%s", color, time_action(), philo->n, str, NC);
	pthread_mutex_unlock(&philo->game->print_mutex);
}

void	ft_sleep_think(t_philo *philo)
{
	print_mutex(philo, PURPLE, "is sleeping\n");
	usleep(philo->game->time_sleep * 1000);
	print_mutex(philo, YELLOW, "is thinking\n");
}

void	ft_eat(t_philo *philo)
{
	print_mutex(philo, CYAN, "is eating\n");
	pthread_mutex_lock(&philo->game->eat_mutex);
	philo->last_meal_ms = time_action();
	pthread_mutex_unlock(&philo->game->eat_mutex);
	usleep(philo->game->time_eat * 1000);
	pthread_mutex_lock(&philo->game->eat_mutex);
	philo->total_meal_eaten += 1;
	if (philo->total_meal_eaten == philo->game->must_eat)
		philo->done_eating_all = true;
	pthread_mutex_unlock(&philo->game->eat_mutex);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	print_mutex(philo, BLUE, "has taken a right fork\n");
	if (philo->game->number_philo == 1)
	{
		usleep(philo->game->time_die * 1000 + 1000);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_mutex(philo, BLUE, "has taken a left fork\n");
}

void	*start_philo(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->n % 2 != 0)
		usleep(philo->game->time_eat * 500);
	while (1)
	{
		pthread_mutex_lock(&philo->game->dead_mutex);
		pthread_mutex_lock(&philo->game->eat_mutex);
		if (philo->game->dead_bool == true || philo->done_eating_all == true)
		{
			pthread_mutex_unlock(&philo->game->eat_mutex);
			pthread_mutex_unlock(&philo->game->dead_mutex);
			break ;
		}	
		pthread_mutex_unlock(&philo->game->eat_mutex);
		pthread_mutex_unlock(&philo->game->dead_mutex);
		take_forks(philo);
		ft_eat(philo);
		ft_sleep_think(philo);
	}
	return (0);
}
