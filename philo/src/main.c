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

void *routine(void *arg) {
	
}


long long get_timestamp_in_milliseconds() {
		struct timeval tv;
		gettimeofday(&tv, NULL); // Get the current time

		// Calculate milliseconds since epoch
		long long milliseconds = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
		return milliseconds;
}
void  check_input(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		printf("wrong number of arguments\n");
	if (ft_is_digit(av[1]))
		{;}
}

void  init_vars(char **av)
{}

int main(int  ac, char **av)
{
	t_philo philo1;

}