/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:26:22 by ltruchel          #+#    #+#             */
/*   Updated: 2022/12/12 19:35:08 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdbool.h>

# define NC "\033[0m"
# define RED "\033[1;31m"

# define E_FORMAT "Wrong format, use 5 or 6 arguments\n"
# define E_DIGIT "Arguments need to be in digits and positive\n"
# define E_OVERFLOW "Arguments need to fit in unsigned int\n"
# define E_NULL "Number of philos and/or meal can't be 0\n"

# define THINKING
# define SLEEPING
# define STARVING
# define EATING

typedef struct s_philo
{
	size_t			n;
	size_t			meal_eaten;
	bool			dead;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_game
{
	size_t			number_philo;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			must_eat;
	long long		time_start;
	t_philo			*philo;
}	t_game;

/* Parsing functions                                                          */

int			ft_parsing(char **av);
int			check_digits_positive(char **av);
int			check_null_args(char **av);
int			check_overflow(char **av);

/* Functions to initialise both game and philo structs                        */

void		init_structs(t_game *game, char **av);
void		get_time_start(t_game *game);
void		init_philos(t_game *game);

/* Functions for philosophers' life                                           */

void		*algo_philo(void *game);

/* Utils                                                                      */

long long	ft_atoui_overflow(const char *str);
size_t		ft_atoui(const char *str);

#endif
