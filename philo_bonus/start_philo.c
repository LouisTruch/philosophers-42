/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:13:05 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/05 15:42:13 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>

void	print_sem(t_philo *philo, char *color, char *str)
{
	sem_wait(philo->game->sem_print);
	printf("%s%lld %i %s%s", color, time_action(), philo->id, str, NC);
	sem_post(philo->game->sem_print);
}

void	ft_sleep_think(t_philo *philo)
{
	print_sem(philo, PURPLE, "is sleeping\n");
	usleep(philo->game->time_sleep * 1000);
	print_sem(philo, YELLOW, "is thinking\n");
}

void	take_forks_eat(t_philo *philo)
{
	sem_wait(philo->game->sem_fork);
	print_sem(philo, BLUE, "has taken a fork\n");
	sem_wait(philo->game->sem_fork);
	print_sem(philo, BLUE, "has taken a fork\n");
	print_sem(philo, CYAN, "is eating\n");
	philo->last_meal_ms = time_action();
	usleep(philo->game->time_eat * 1000);
	philo->total_meal_eaten += 1;
	sem_post(philo->game->sem_fork);
	sem_post(philo->game->sem_fork);
}

/* Detached thread from each philo to check if it is dead                    *
 * If it is, block other philos from printing and increment sem_end          *
 * Also need to break if philo is done eating to end thread and avoid leaks  */

void	*check_death(void *philo_cast)
{
	t_philo	*philo;

	philo = (t_philo *)philo_cast;
	while (1)
	{
		usleep(100);
		if (time_action() - philo->last_meal_ms
			> (long long)philo->game->time_die)
		{
			print_sem(philo, RED, " died\n");
			sem_wait(philo->game->sem_print);
			sem_post(philo->game->sem_end);
			break ;
		}
		if (philo->game->must_eat
			&& philo->total_meal_eaten == philo->game->must_eat)
		{
			break ;
		}
	}
	return (NULL);
}

/* Create and detach a thread that check if philo is dead                    *
 * Then start philo's routine                                                *
 * Return if philo is done eating to stop process                            */

void	start_philo(t_philo *philo)
{
	pthread_t	own_checker_death;

	pthread_create(&own_checker_death, NULL, check_death, philo);
	pthread_detach(own_checker_death);
	while (1)
	{
		take_forks_eat(philo);
		if (philo->total_meal_eaten == philo->game->must_eat)
			return ;
		ft_sleep_think(philo);
	}
}
