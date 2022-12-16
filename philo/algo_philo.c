/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:25:51 by ltruchel          #+#    #+#             */
/*   Updated: 2022/12/16 17:05:44 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mutex(t_philo *philo, char *color, char *str)
{
	pthread_mutex_lock(&philo->game->print_mutex);
	pthread_mutex_lock(&philo->game->dead_mutex);
	if (philo->game->dead_bool == 1)
	{
		pthread_mutex_unlock(&philo->game->dead_mutex);
		pthread_mutex_unlock(&philo->game->print_mutex);
		return ;
	}
	printf("%s%lld %zu %s%s", color, time_action(), philo->n, str, NC);
	pthread_mutex_unlock(&philo->game->dead_mutex);
	pthread_mutex_unlock(&philo->game->print_mutex);
}

void	ft_sleep(t_philo *philo)
{
/*	pthread_mutex_lock(&philo->game->dead_mutex);
	if (philo->game->dead_bool == 1)
	{
		pthread_mutex_unlock(&philo->game->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->game->dead_mutex);*/
	print_mutex(philo, PURPLE, "is sleeping\n");
	usleep(philo->game->time_sleep * 1000);
/*	pthread_mutex_lock(&philo->game->dead_mutex);
	if (philo->game->dead_bool == 1)
	{
		pthread_mutex_unlock(&philo->game->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->game->dead_mutex);*/
	print_mutex(philo, YELLOW, "is thinking\n");
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->dead_mutex);
	if (philo->game->dead_bool == 1)
	{
		pthread_mutex_unlock(&philo->game->dead_mutex);
		pthread_mutex_lock(&philo->game->think_mutex);
		if (philo->eating == 1)
		{
			pthread_mutex_unlock(&philo->game->think_mutex);
			pthread_mutex_unlock(&(philo->r_fork));
			pthread_mutex_unlock(philo->l_fork);
			return ;
		}
		pthread_mutex_unlock(&philo->game->think_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->game->dead_mutex);
	print_mutex(philo, CYAN, "is eating\n");
	pthread_mutex_lock(&philo->game->dead_mutex);
	philo->last_meal_ms = time_action();
	pthread_mutex_unlock(&philo->game->dead_mutex);
	usleep(philo->game->time_eat * 1000);
	pthread_mutex_lock(&philo->game->dead_mutex);
	philo->total_meal_eaten += 1;
	philo->last_meal_ms = time_action();
	pthread_mutex_lock(&philo->game->pick_mutex);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->game->pick_mutex);
	pthread_mutex_unlock(&philo->game->dead_mutex);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(&(philo->r_fork));
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->dead_mutex);
	if (philo->game->dead_bool == 1)
	{
		pthread_mutex_unlock(&philo->game->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->game->dead_mutex);
	pthread_mutex_lock(&(philo->r_fork));
	pthread_mutex_lock(&philo->game->pick_mutex);
	philo->eating = 1;
	pthread_mutex_unlock(&philo->game->pick_mutex);
	print_mutex(philo, BLUE, "has taken a right fork\n");
	pthread_mutex_lock(philo->l_fork);
	print_mutex(philo, BLUE, "has taken a left fork\n");
}

void	single_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->r_fork));
	print_mutex(philo, BLUE, "has taken a fork\n");
	usleep(philo->game->time_die * 1000);
	pthread_mutex_unlock(&(philo->r_fork));
	return ;
}

void	*algo_philo(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	usleep(50);
	if (philo->game->number_philo == 1)
	{
		single_philo(philo);
		return (NULL);
	}	
	if (philo->n % 2 == 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(&philo->game->dead_mutex);
		if ((philo->game->must_eat != 0
				&& philo->total_meal_eaten == philo->game->must_eat)
			|| philo->game->dead_bool == 1)
		{
			pthread_mutex_unlock(&philo->game->dead_mutex);
			philo->done_must_eat = 1;
			break ;
		}
		pthread_mutex_unlock(&philo->game->dead_mutex);
		take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (0);
}
