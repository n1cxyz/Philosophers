/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:33:41 by dasal             #+#    #+#             */
/*   Updated: 2024/11/27 11:33:43 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_sim(t_philo *philos)
{
	int	i;

	i = 0;
	philos->vars->start_time = get_time();
	while (i < philos->vars->nmb_of_philos)
	{
		(philos + i)->last_meal = get_time();
		if (pthread_create(&(philos + i)->id, NULL, &routine, philos + i))
			error_exit("Error\nCreate philo fail\n");
		usleep(500);
		i++;
	}
	if (pthread_create(&philos->vars->monitor, NULL, &monitoring, philos))
		error_exit("Error\nCreate monitor fail\n");
	if (pthread_join(philos->vars->monitor, NULL))
		error_exit("Error\nJoin monitor fail\n");
	i = 0;
	while (i < philos->vars->nmb_of_philos)
	{
		if (pthread_join((philos + i)->id, NULL))
			error_exit("Error\nJoin philo fail\n");
		i++;
	}
	destroy_mutex(philos);
}

void	*routine(void	*args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (get_is_running(philo->vars))
	{
		pthread_mutex_lock(philo->l_fork);
		put_msg(philo, "has taken a fork");
		if (philo->vars->nmb_of_philos == 1)
		{
			pthread_mutex_unlock(philo->l_fork);
			break ;
		}
		pthread_mutex_lock(philo->r_fork);
		put_msg(philo, "has taken a fork");
		put_msg(philo, "is eating");
		set_last_meal(philo);
		ft_sleep(philo->vars, philo->vars->time_to_eat);
		if (get_is_running(philo->vars))
			set_meals_ate(philo);
		unlock_forks(philo);
		put_msg(philo, "is sleeping");
		ft_sleep(philo->vars, philo->vars->time_to_sleep);
		put_msg(philo, "is thinking");
	}
	return (0);
}

void	*monitoring(void	*args)
{
	int		i;
	int		stop_flag;
	t_philo	*philos;

	philos = (t_philo *)args;
	while (get_is_running(philos->vars))
	{
		i = 0;
		stop_flag = 0;
		while (i < philos->vars->nmb_of_philos)
		{
			if ((get_time() - get_last_meal(philos + i)) > 
				philos->vars->time_to_die)
			{
				put_msg(philos + i, "died");
				set_is_running(philos->vars, 0);
				break ;
			}
			check_and_stop(philos, i, &stop_flag);
			i++;
		}
		if (stop_flag == philos->vars->nmb_of_philos)
			set_is_running(philos->vars, 0);
	}
	return (0);
}

void	put_msg(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->vars->message);
	if (get_is_running(philo->vars))
		printf("%lld %d %s\n", 
			get_time() - philo->vars->start_time, philo->number, message);
	pthread_mutex_unlock(&philo->vars->message);
}

void	destroy_mutex(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->vars->nmb_of_forks)
	{
		pthread_mutex_destroy(&philos->vars->forks[i]);
		pthread_mutex_destroy(&(philos + i)->meal_mutex);
		pthread_mutex_destroy(&(philos + i)->meals_ate_mutex);
		i++;
	}
	pthread_mutex_destroy(&philos->vars->message);
	pthread_mutex_destroy(&philos->vars->running_mutex);
	free(philos->vars->forks);
	free(philos->vars);
	free(philos);
}
