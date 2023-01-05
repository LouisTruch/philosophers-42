/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:09:57 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/05 14:07:53 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_game *game)
{
	sem_close(game->sem_fork);
	sem_close(game->sem_print);
	sem_close(game->sem_end);
	free(game->philo);
	free(game->pid);
}

size_t	ft_atoui(const char *str)
{
	long long	rslt;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	rslt = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rslt = rslt * 10 + str[i] - '0';
		i++;
	}	
	return (rslt * sign);
}

long long	ft_atoui_overflow(const char *str)
{
	long long	rslt;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	rslt = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rslt = rslt * 10 + str[i] - '0';
		if (rslt * sign > 4294967295 || rslt * sign < 0)
			return (-1);
		i++;
	}	
	return (rslt * sign);
}

int	is_number_av(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
