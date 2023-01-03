/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:10:34 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/03 16:36:47 by ltruchel         ###   ########.fr       */
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

# define NC		"\033[0m"
# define B_RED	"\033[1;31m"
# define RED	"\033[0;31m"
# define BLUE	"\033[0;34m"
# define CYAN	"\033[0;36m"
# define PURPLE	"\033[0;35m"
# define YELLOW	"\033[0;33m"

# define E_FORMAT	"Wrong format, use 5 or 6 arguments\n"
# define E_ONLY_DIGIT	"Use only digits in args\n"
# define E_DIGIT_POSITIVE	"Arguments need to be in digits and positive\n"
# define E_OVERFLOW	"Arguments need to fit in unsigned int\n"
# define E_NULL		"Number of philos and/or meal can't be 0\n"

typedef struct s_philo
{
	size_t				n;
	size_t				total_meal_eaten;
	bool				done_eating_all;
	long long			last_meal_ms;
	pthread_t			thread;
	pthread_mutex_t		r_fork;
	pthread_mutex_t		*l_fork;
	struct s_game		*game;
}	t_philo;

typedef struct s_game
{
	size_t			number_philo;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			must_eat;
	bool			dead_bool;
	pthread_t		manager_philo;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	eat_mutex;
	t_philo			*philo;
}	t_game;

/* Parsing functions                                                          */

int			ft_parsing(char **av);
int			check_digits_positive(char **av);
int			check_null_args(char **av);
int			check_overflow(char **av);

/* Functions to initialise both game and philo structs                        */

void		init_struct(t_game *game, char **av);
void		get_time_start(t_game *game);
long long	time_action(void);
void		init_philo(t_game *game);

/* Functions for philosophers' life                                           */

void		*start_philo(void *game);
void		print_mutex(t_philo *philo, char *color, char *str);

/* Utils                                                                      */

long long	ft_atoui_overflow(const char *str);
size_t		ft_atoui(const char *str);
int			is_number_av(char **ag);

#endif

