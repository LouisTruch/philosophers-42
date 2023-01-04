/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:13:05 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/04 19:54:16 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

void	print_sem(t_philo *philo, char *color, char *str)
{
	sem_wait(philo->game->sem_death);
	sem_wait(philo->game->sem_print);
	printf("%s%lld %i %s%s", color, time_action(), philo->id, str, NC);
	sem_post(philo->game->sem_death);
	sem_post(philo->game->sem_print);
}

void	ft_sleep_think(t_philo *philo)
{
	print_sem(philo, PURPLE, "is sleeping\n");
	usleep(philo->game->time_sleep * 1000);
	print_sem(philo, YELLOW, "is thinking\n");
}

void	ft_eat(t_philo *philo)
{
	print_sem(philo, CYAN, "is eating\n");
	philo->last_meal_ms = time_action();
	usleep(philo->game->time_eat * 1000);
	philo->total_meal_eaten += 1;
	if (philo->total_meal_eaten == philo->game->must_eat)
	{
		philo->done_eating_all = true;
		print_sem(philo, RED, " is done eating\n");
	}
	sem_post(philo->game->sem_fork);
	sem_post(philo->game->sem_fork);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->game->sem_fork);
	print_sem(philo, BLUE, "has taken a fork\n");
	sem_wait(philo->game->sem_fork);
	print_sem(philo, BLUE, "has taken a fork\n");
}

void	*check_death(void *philo_cast)
{
	t_philo	*philo;

	philo = (t_philo *)philo_cast;
	while (1)
	{
		usleep(1000);
		if (time_action() - philo->last_meal_ms
			> (long long)philo->game->time_die)
		{
			print_sem(philo, RED, " died\n");
			sem_post(philo->game->sem_test);
			break ;
		}
	}
	return (NULL);
}

void	start_philo(t_philo *philo)
{
	pthread_create(&philo->checker, NULL, check_death, philo);
	if (philo->id % 2 == 0)
		usleep(philo->game->time_eat * 500);
	while (1)
	{
		take_forks(philo);
		ft_eat(philo);
		if (philo->done_eating_all == true)
			break ;
		ft_sleep_think(philo);
	}
}
