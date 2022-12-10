/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:59:38 by ltruchel          #+#    #+#             */
/*   Updated: 2022/12/09 19:52:41 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parsing(char **av)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (ft_atoi_overflow(av[i]) <= 0
			|| ft_atoi_overflow(av[i]) == 2147483648)
		{
			printf(ERROR_NB);
			return (0);
		}
		i++;
	}
	if (av[i])
	{
		if (ft_atoi_overflow(av[5]) == 2147483648)
		{
			printf(ERROR_NB);
			return (0);
		}
	}
	return (1);
}

long long	ft_atoi_overflow(const char *str)
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
		if (rslt * sign > INT_MAX || rslt * sign < INT_MIN)
			return (2147483648);
		i++;
	}	
	return (rslt * sign);
}
