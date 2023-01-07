/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:13:05 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/07 16:46:11 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_sem(t_philo *philo, char *color, char *str)
{
	sem_wait(philo->game->sem_print);
	printf("%s%lld %i %s%s", color, time_action(), philo->id, str, NC);
	if (!ft_strcmp(color, RED))
		return ;
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
	sem_wait(philo->game->sem_eat);
	philo->last_meal_ms = time_action();
	sem_post(philo->game->sem_eat);
	usleep(philo->game->time_eat * 1000);
	sem_wait(philo->game->sem_eat);
	philo->total_meal_eaten += 1;
	sem_post(philo->game->sem_eat);
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
		sem_wait(philo->game->sem_eat);
		if (time_action() - philo->last_meal_ms
			> (long long)philo->game->time_die)
		{
			print_sem(philo, RED, " died\n");
			sem_post(philo->game->sem_end);
			break ;
		}
		if (philo->game->must_eat
			&& philo->total_meal_eaten == philo->game->must_eat)
		{
			sem_post(philo->game->sem_eat);
			break ;
		}
		sem_post(philo->game->sem_eat);
	}
	return (NULL);
}

/* Create and detach a thread that check if philo is dead                    *
 * Then start philo's routine                                                *
 * Return if philo is done eating to stop process                            */

void	start_philo(t_philo *philo)
{
	pthread_t	own_checker_death;

	if (philo->id % 2)
		usleep(50000);
	pthread_create(&own_checker_death, NULL, check_death, philo);
	pthread_detach(own_checker_death);
	while (1)
	{
		usleep(100);
		take_forks_eat(philo);
		if (philo->total_meal_eaten == philo->game->must_eat)
		{
			usleep(philo->game->time_die * 1000);
			return ;
		}
		ft_sleep_think(philo);
	}
}
