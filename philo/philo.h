/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:26:22 by ltruchel          #+#    #+#             */
/*   Updated: 2022/12/10 19:06:32 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>

# define ERROR_FORMAT "\033[1;31mWrong format, need 4 arguments\n\033[0m"
# define ERROR_NB "\033[1;31mOne arg either is <= 0 or overflow\n\033[0m"

# define THINKING
# define SLEEPING
# define STARVING
# define EATING

typedef struct s_philo
{
	bool			dead;
	pthread_mutex_t	right;
	pthread_mutex_t	*left;
}	t_philo;

typedef struct s_game
{
	unsigned int		n;
	unsigned int		time_die;
	unsigned int		time_eat;
	unsigned int		time_sleep;
	unsigned int		must_eat;
	unsigned long long	time_start;
	unsigned long long	actual_time;
	t_philo				*philo;
}	t_game;

/* Parsing functions                                                          */

int				ft_parsing(char **av);
long long		ft_atoi_overflow(const char *str);
unsigned int	ft_atoui(const char *str);

/* Functions to initialise both game and philo structs                        */

void			initialise_structs(t_game *game, char **av);
void			get_time_start(t_game **game);
void			initialise_philos(t_game **game);

#endif
