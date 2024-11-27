/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:33:47 by dasal             #+#    #+#             */
/*   Updated: 2024/11/27 11:33:48 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_is_running(t_vars *vars)
{
	int	value;

	pthread_mutex_lock(&vars->running_mutex);
	value = vars->is_running;
	pthread_mutex_unlock(&vars->running_mutex);
	return (value);
}

void	set_is_running(t_vars *vars, int value)
{
	pthread_mutex_lock(&vars->running_mutex);
	vars->is_running = value;
	pthread_mutex_unlock(&vars->running_mutex);
}

long long int	get_last_meal(t_philo *philo)
{
	long long int	meal_time;

	pthread_mutex_lock(&philo->meal_mutex);
	meal_time = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (meal_time);
}

void	set_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->meal_mutex);
}
