/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:14:50 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/07 14:56:31 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parsing(char **av)
{
	if (is_number_av(av) != 0)
	{
		printf("%s%s%s", B_RED, E_ONLY_DIGIT, NC);
		return (1);
	}
	if (check_digits_positive(av) != 0)
	{
		printf("%s%s%s", B_RED, E_DIGIT_POSITIVE, NC);
		return (2);
	}
	if (check_overflow(av) != 0)
	{
		printf("%s%s%s", B_RED, E_OVERFLOW, NC);
		return (3);
	}
	if (check_null_args(av) != 0)
	{
		printf("%s%s%s%s", B_RED, E_NULL, E_NUMBER_PHILO, NC);
		return (4);
	}
	return (0);
}

int	check_digits_positive(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if ((av[i][j] < '0' && av[i][j] > '9' ) || av[i][j] == '-')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_overflow(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoui_overflow(av[i]) == -1)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_null_args(char **av)
{
	if (ft_atoui(av[1]) == 0 || ft_atoui(av[1]) > 500)
		return (1);
	if (av[5])
	{
		if (ft_atoui(av[5]) == 0)
			return (1);
	}
	return (0);
}
