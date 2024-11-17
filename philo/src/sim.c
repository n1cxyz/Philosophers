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
		pthread_detach((philos + i)->id);
		usleep(50);
		i++;
	}
	if (pthread_create(&philos->vars->monitor, NULL, &monitoring, philos))
		error_exit("Error\nCreate monitor fail\n");
	if (pthread_join(philos->vars->monitor, NULL))
		error_exit("Error\nJoin monitor fail\n");
	destroy_mutex(philos);
}

void	*routine(void	*args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	while (philo->vars->is_running)
	{
		put_msg(philo, "is thinking");
		pthread_mutex_lock(philo->l_fork);
		put_msg(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		put_msg(philo, "has taken a fork");
		put_msg(philo, "is eating");
		ft_sleep(philo->vars, philo->vars->time_to_eat);
		philo->last_meal = get_time();
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		if (philo->vars->is_running)
			philo->meals_ate++;
		put_msg(philo, "is sleeping");
		ft_sleep(philo->vars, philo->vars->time_to_sleep);
	}
	return (0);
}

void	*monitoring(void	*args)
{
	int		i;
	int		stop_flag;
	t_philo *philos;

	philos = (t_philo *)args;
	while (philos->vars->is_running)
	{
		i = 0;
		stop_flag = 0;
		while (i < philos->vars->nmb_of_philos)
		{
			if (get_time() - (philos + i)->last_meal > philos->vars->time_to_die)
			{
				put_msg(philos + i, "died");
				philos->vars->is_running = 0;
				break ;
			}
			if (philos->vars->nmb_of_meals != -2 && 
				(philos + i)->meals_ate >= philos->vars->nmb_of_meals)
				stop_flag++;
			i++;
		}
		if (stop_flag == philos->vars->nmb_of_philos)
			philos->vars->is_running = 0;
	}
	return (0);
}

void	put_msg(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->vars->message);
	if (philo->vars->is_running)
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
		i++;
	}
	pthread_mutex_destroy(&philos->vars->message);
}