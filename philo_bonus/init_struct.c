/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:34:58 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/04 19:52:28 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	game->dead_bool = false;
	sem_unlink("semFork");
	sem_unlink("semPrint");
	sem_unlink("semDeath");
	sem_unlink("semTest");
	game->sem_fork = sem_open("semFork", O_CREAT, 0660, game->number_philo);
	game->sem_print = sem_open("semPrint", O_CREAT, 0660, 1);
	game->sem_death = sem_open("semDeath", O_CREAT, 0660, 1);
	game->sem_test = sem_open("semTest", O_CREAT, 0660, 0);
	if (game->sem_fork == SEM_FAILED)
	{
		// add error message if sem_open failed
		exit (0);
	}

}

void	start_process(t_game *game)
{
	int		i;
	pid_t	*pid;

	i = 0;
	pid = malloc(sizeof(pid_t) * game->number_philo);
	game->philo = malloc(sizeof(t_philo) * game->number_philo);
	if (!game->philo)
	{
		//add error message
		exit (0);
	}
	while (i < game->number_philo)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			// add error fork didnt work
			exit (0);
		}
		else if (pid[i] == 0)
		{
			init_philo(game, &game->philo[i], i);
			free(game->philo);
			exit (0);
		}
		i++;
	}
//	waitpid(0, NULL, 0);
//	for (int j = 0 ; j < game->number_philo ; j++)
//		printf("pid=%i\n", pid[j]);
	sem_wait(game->sem_test);
	i = 0;
	while (i < game->number_philo)
	{
		kill(pid[i], SIGKILL);
		i++;
	}
	free(game->philo);
	free(pid);
}

void	init_philo(t_game *game, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->total_meal_eaten = 0;
	philo->done_eating_all = false;
	philo->last_meal_ms = time_action();
	philo->game = game;
	start_philo(philo);
}
