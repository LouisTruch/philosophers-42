/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltruchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:26:04 by ltruchel          #+#    #+#             */
/*   Updated: 2022/12/12 18:07:18 by ltruchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac < 5 || ac > 6)
	{
		printf("%s%s%s", RED, E_FORMAT, NC);
		return (1);
	}
	if (ft_parsing(av) != 0)
		return (1);
	init_structs(&game, av);
	return (0);
}
