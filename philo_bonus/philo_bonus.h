/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:10:34 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/07 16:49:00 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdbool.h>

# define NC		"\033[0m"
# define B_RED	"\033[1;31m"
# define RED	"\033[0;31m"
# define BLUE	"\033[0;34m"
# define CYAN	"\033[0;36m"
# define PURPLE	"\033[0;35m"
# define YELLOW	"\033[0;33m"

# define E_FORMAT			"Wrong format, use 5 or 6 arguments\n"
# define E_ONLY_DIGIT		"Use only digits in args\n"
# define E_DIGIT_POSITIVE	"Arguments need to be in digits and positive\n"
# define E_OVERFLOW			"Arguments need to fit in unsigned int\n"
# define E_NULL				"Number of philos and meal can't be 0\n"
# define E_NUMBER_PHILO		"Also number of philo can't be > 500\n"

# define DONE_EATING 45

typedef struct s_philo
{
	int					id;
	size_t				total_meal_eaten;
	long long			last_meal_ms;
	struct s_game		*game;
}	t_philo;

typedef struct s_game
{
	int				number_philo;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			must_eat;
	pid_t			*pid;
	sem_t			*sem_fork;
	sem_t			*sem_print;
	sem_t			*sem_end;
	sem_t			*sem_eat;
	sem_t			*sem_clean;
	t_philo			*philo;
}	t_game;

/* Parsing functions                                                          */

int			ft_parsing(char **av);
int			check_digits_positive(char **av);
int			check_args(char **av);
int			check_overflow(char **av);

/* Functions to initialise both game and philo structs                        */

void		init_struct(t_game *game, char **av);
void		start_process(t_game *game);
void		init_philo(t_game *game, t_philo *philo, int i);

/* Time function                                                              */

long long	time_action(void);

/* Functions for philosophers' life                                           */

void		start_philo(t_philo *philo);

/* Utils                                                                      */

void		ft_free(t_game *game);
long long	ft_atoui_overflow(const char *str);
size_t		ft_atoui(const char *str);
int			is_number_av(char **ag);
int			ft_strcmp(const char *s1, const char *s2);

#endif
