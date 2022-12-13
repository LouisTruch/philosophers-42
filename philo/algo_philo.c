/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:25:51 by ltruchel          #+#    #+#             */
/*   Updated: 2022/12/13 21:38:22 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	is_dead(t_philo *philo)
{
	if (philo->game->dead == 1)
		return (1);
	if (time_action() - philo->last_meal_ms > (long long)philo->game->time_die)
	{
		philo->game->dead = 1;
		printf("%s%lld %zu died\n%s",
			RED, time_action(), philo->n, NC);
		return (1);
	}
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	if (philo->game->dead == 1)
		return ;
	printf("%s%lld %zu is sleeping\n%s",
		PURPLE, time_action(), philo->n, NC);
	usleep(philo->game->time_sleep * 1000);
	if (philo->game->dead == 1)
		return ;
	printf("%s%lld %zu is thinking\n%s",
		YELLOW, time_action(), philo->n, NC);
}

void	ft_eat(t_philo *philo)
{
	if (philo->game->dead == 1)
		return ;
	printf("%s%lld %zu is eating\n%s",
		CYAN, time_action(), philo->n, NC);
	usleep(philo->game->time_eat * 1000);
	pthread_mutex_unlock(&(philo->r_fork));
	pthread_mutex_unlock(philo->l_fork);
	philo->total_meal_eaten += 1;
	philo->last_meal_ms = time_action();
	philo->eating = 0;
}

void	take_forks(t_philo *philo)
{
	if (philo->game->dead == 1)
		return ;
	pthread_mutex_lock(&(philo->r_fork));
	philo->eating = 1;
	printf("%s%lld %zu has taken a right fork \n%s",
		BLUE, time_action(), philo->n, NC);
	if (philo->game->number_philo == 1)
	{
		usleep(philo->game->time_die * 1000);
		pthread_mutex_unlock(philo->l_fork);
		philo->game->dead = 1;
		printf("%s%lld %zu died\n%s",
			RED, time_action(), philo->n, NC);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	printf("%s%lld %zu has taken a left fork \n%s",
		BLUE, time_action(), philo->n, NC);
}

void	*algo_philo(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->n % 2 == 0)
		usleep(philo->game->time_eat * 1000);
	while (is_dead(philo) == 0)
	{
		if (philo->total_meal_eaten == philo->game->must_eat)
			break ;
//		if (philo->game->philo[philo->prev].eating == 1 || philo->game->philo[philo->next].eating == 1 || philo->total_meal_eaten > philo->game->philo[philo->prev].total_meal_eaten || philo->total_meal_eaten > philo->game->philo[philo->next].total_meal_eaten)
//			usleep(10);
		else
		{
			take_forks(philo);
			ft_eat(philo);
			ft_sleep(philo);
		}
	}
	return (0);
}
