/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:42:30 by dasal             #+#    #+#             */
/*   Updated: 2024/10/09 12:42:43 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_philo	*philos;

	if (ac >= 5 && ac <= 6)
	{
		if (init(&philos, ac, av) == -1)
			return (1);
		start_sim(philos);
	}
	else
		printf("Error\nWrong number of arguments\n");
	return (0);
}
