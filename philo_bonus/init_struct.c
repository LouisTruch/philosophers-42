/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 14:34:58 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/05 14:44:09 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <semaphore.h>

/* Function to init game struct, unlink and init all semaphores               */

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
	sem_unlink("semFork");
	sem_unlink("semPrint");
	sem_unlink("semEnd");
	sem_unlink("semEat");
	game->sem_fork = sem_open("semFork", O_CREAT, 0660, game->number_philo);
	game->sem_print = sem_open("semPrint", O_CREAT, 0660, 1);
	game->sem_print = sem_open("semEat", O_CREAT, 0660, 1);
	game->sem_end = sem_open("semEnd", O_CREAT, 0660, 0);
	if (game->sem_fork == SEM_FAILED || game->sem_print == SEM_FAILED
		|| game->sem_end == SEM_FAILED)
		exit (EXIT_FAILURE);
}

/* Function to init every philo struct then start philo's routine             */

void	init_philo(t_game *game, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->total_meal_eaten = 0;
	philo->last_meal_ms = time_action();
	philo->game = game;
	start_philo(philo);
}

/* Wait for every child(philo) to eat their n meals                          *
 * If they all did, unlock sem_end to kill every child                       */

void	*ft_check_done_eating(void *game_cast)
{
	t_game	*game;
	int		i;

	i = 0;
	game = (t_game *)game_cast;
	while (i < game->number_philo)
	{
		waitpid(game->pid[i], NULL, 0);
		i++;
	}
	sem_post(game->sem_end);
	return (NULL);
}

/* Parent thread : Detach a thread to check if philos are done eating        *
 * Then wait for the sem_end to be incremented when one philo is dead        *
 * Or they are done eating                                                   *
 * Need usleep for every threads inside each philo to return to avoid leaks  */

void	start_checker_thread(t_game *game)
{
	int			i;
	pthread_t	check_done_eating;

	pthread_create(&check_done_eating, NULL, ft_check_done_eating, game);
	pthread_detach(check_done_eating);
	sem_wait(game->sem_end);
	i = 0;
	while (i < game->number_philo)
	{
		kill(game->pid[i], SIGKILL);
		i++;
	}
	usleep(game->time_die * 1000);
	ft_free(game);
	exit (EXIT_SUCCESS);
}

/* Fork 1 time for each philo, then initialise then                          * 
 * Use the main process to check if there is one dead                        *
 * Or if they are done eating                                                */

void	start_process(t_game *game)
{
	int			i;

	i = 0;
	game->pid = malloc(sizeof(pid_t) * game->number_philo);
	game->philo = malloc(sizeof(t_philo) * game->number_philo);
	if (!game->philo || !game->pid)
		exit (EXIT_FAILURE);
	while (i < game->number_philo)
	{
		game->pid[i] = fork();
		usleep(500);
		if (game->pid[i] == -1)
			exit (EXIT_FAILURE);
		else if (game->pid[i] == 0)
		{
			init_philo(game, &game->philo[i], i);
			usleep(game->time_die);
			ft_free(game);
			exit (EXIT_SUCCESS);
		}
		i++;
	}
	start_checker_thread(game);
}
