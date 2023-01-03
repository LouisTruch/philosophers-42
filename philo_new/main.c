/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:11:03 by ltruchel          #+#    #+#             */
/*   Updated: 2023/01/03 12:17:11 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac < 5 || ac > 6)
	{
		printf("%s%s%s", B_RED, E_FORMAT, NC);
		return (1);
	}
	if (ft_parsing(av) != 0)
		return (2);
	init_struct(&game, av);
	return (0);
}
