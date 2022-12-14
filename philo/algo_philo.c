/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:25:51 by ltruchel          #+#    #+#             */
/*   Updated: 2022/12/14 17:58:20 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_mutex(t_philo *philo, char *color, char *str)
{
	pthread_mutex_lock(&philo->game->print_mutex);
	pthread_mutex_lock(&philo->game->dead_mutex);
	if (philo->game->dead_bool == 1)
	{
		pthread_mutex_unlock(&philo->game->print_mutex);
		pthread_mutex_unlock(&philo->game->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->game->print_mutex);
	pthread_mutex_unlock(&philo->game->dead_mutex);
	printf("%s%lld %zu %s%s", color, time_action(), philo->n, str, NC);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->dead_mutex);
	if (philo->game->dead_bool == 1)
	{
		pthread_mutex_unlock(&philo->game->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->game->dead_mutex);
	print_mutex(philo, PURPLE, "is sleeping\n");
	usleep(philo->game->time_sleep * 1000);
	pthread_mutex_lock(&philo->game->dead_mutex);
	if (philo->game->dead_bool == 1)
	{
		pthread_mutex_unlock(&philo->game->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->game->dead_mutex);
	print_mutex(philo, YELLOW, "is thinking\n");
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->game->dead_mutex);
	if (philo->game->dead_bool == 1)
	{
		pthread_mutex_unlock(&(philo->r_fork));
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->game->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->game->dead_mutex);
	print_mutex(philo, CYAN, "is eating\n");
	philo->last_meal_ms = time_action();
	usleep(philo->game->time_eat * 1000);
	philo->total_meal_eaten += 1;
	philo->last_meal_ms = time_action();
	philo->eating = 0;
	pthread_mutex_unlock(&(philo->r_fork));
	pthread_mutex_unlock(philo->l_fork);
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
	philo->eating = 1;
	print_mutex(philo, BLUE, "has taken a right fork\n");
	if (philo->game->number_philo == 1)
	{
		usleep(philo->game->time_die * 1000);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print_mutex(philo, BLUE, "has taken a left fork\n");
}

void	*algo_philo(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->n % 2 == 0)
		usleep(philo->game->time_eat * 1000);
	while (philo->game->dead_bool == 0)
	{
		if (philo->game->must_eat != 0
			&& philo->total_meal_eaten == philo->game->must_eat)
		{
			philo->done_must_eat = 1;
			break ;
		}
		if (philo->game->philo[philo->prev].eating == 1 || philo->game->philo[philo->next].eating == 1) // || philo->total_meal_eaten > philo->game->philo[philo->prev].total_meal_eaten || philo->total_meal_eaten > philo->game->philo[philo->next].total_meal_eaten)
			usleep(5);
		else
		{
			take_forks(philo);
			ft_eat(philo);
			ft_sleep(philo);
		}
	}
	return (0);
}
