/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:34:23 by dasal             #+#    #+#             */
/*   Updated: 2024/11/27 11:34:25 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_meals_ate(t_philo *philo)
{
	int	meals_ate;

	pthread_mutex_lock(&philo->meal_mutex);
	meals_ate = philo->meals_ate;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (meals_ate);
}

void	set_meals_ate(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meals_ate++;
	pthread_mutex_unlock(&philo->meal_mutex);
}

void	check_and_stop(t_philo *philos, int i, int *stop_flag)
{
	if (philos->vars->nmb_of_meals != -2 && 
		get_meals_ate(philos + i) >= philos->vars->nmb_of_meals)
		(*stop_flag)++;
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
