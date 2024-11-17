#include "philo.h"

int	init_vars(t_vars **vars, int ac, char **av)
{

	t_vars *tmp;

	tmp = (t_vars *)malloc(sizeof(t_vars));
	if (!tmp)
		return (error_exit("Error\nMalloc failed\n"));
	tmp->nmb_of_philos = atoi(av[1]);
	tmp->nmb_of_forks = atoi(av[1]);
	tmp->time_to_die = atoi(av[2]);
	tmp->time_to_eat = atoi(av[3]);
	tmp->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		tmp->nmb_of_meals = atoi(av[5]);
	else
		tmp->nmb_of_meals = -2;
	if (tmp->nmb_of_philos < 1 || tmp->nmb_of_philos > 250 || 
		tmp->time_to_die == -1 || tmp->time_to_eat == -1 || 
		tmp->time_to_sleep == -1 || tmp->nmb_of_meals == -1)
		return (error_exit("Error\nIncorrect argument\n"));
	tmp->is_running = 1;
	*vars = tmp;
	return (0);
}

int	init_forks(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	vars->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * 
		vars->nmb_of_forks);
	if (!vars->forks)
		return (error_exit("Error\nForks malloc failed\n"));
	while (i < vars->nmb_of_forks)
	{
		if (pthread_mutex_init(vars->forks + i, NULL))
		{
			while (j < i)
			{
				pthread_mutex_destroy(&vars->forks[j]);
				j++;
			}
			return (error_exit("Error\nMutex init\n"));
		}
		i++;
	}
	return (0);
}

void	init_philo(t_vars *vars, t_philo *philo, pthread_mutex_t *forks, int i)
{
	philo->number = i + 1;
	philo->meals_ate = 0;
	philo->last_meal = 0;
	philo->vars = vars;
	if (i == 0)
	{
		philo->l_fork = forks + (vars->nmb_of_philos - 1);
		philo->r_fork = forks + i;
	}
	else
	{
		philo->l_fork = forks + (i - 1);
		philo->r_fork = forks + i;
	}
}

int	init(t_philo **philos, int ac, char **av)
{
	t_philo	*tmp;
	t_vars	*vars;
	int		i;

	i = -1;
	if (init_vars(&vars, ac, av) == -1)
		return (-1);
	if (pthread_mutex_init(&vars->message, NULL))
		return (error_exit("Error\nMutex init\n"));
	if (init_forks(vars))
		return (-1);
	tmp = (t_philo *)malloc(sizeof(t_philo) * vars->nmb_of_philos);
	if (!tmp)
		return (error_exit("Error\nPhilos malloc"));
	while (++i < vars->nmb_of_philos)
	{
		init_philo(vars, tmp + i, vars->forks, i);
		//i++;
	}
	*philos = tmp;
	return (0);	
}

int	error_exit(char *message)
{
	printf("%s\n", message);
	return (-1);
}