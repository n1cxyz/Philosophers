/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:39:14 by dasal             #+#    #+#             */
/*   Updated: 2024/10/09 12:42:22 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}				t_state;

typedef struct s_vars
{
	int				nmb_of_forks;
	int				nmb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nmb_of_meals;
	int				is_running;
	long long int	start_time;
	pthread_t		monitor;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	pthread_mutex_t	running_mutex;
}				t_vars;

typedef struct s_philo
{
	t_state			state;
	int				number;
	int				meals_ate;
	long long int	last_meal;
	pthread_mutex_t	meals_ate_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_t		id;
	t_vars			*vars;
}				t_philo;

//		INIT
int				init_vars(t_vars **vars, int ac, char **av);
int				init_forks(t_vars *vars);
void			init_philo(t_vars *vars, t_philo *philo, 
					pthread_mutex_t *forks, int i);
int				init(t_philo **philos, int ac, char **av);
int				error_exit(char *message);

//		SIM
void			start_sim(t_philo *philos);
void			*routine(void	*args);
void			*monitoring(void	*args);
void			put_msg(t_philo *philo, char *message);
void			destroy_mutex(t_philo *philos);

//		UTILS
int				atoi(const char *str);
int				is_space(int c);
int				is_digit(int c);
unsigned int	get_time(void);
void			ft_sleep(t_vars *vars, long long time);

//		UTILS_1
int				get_is_running(t_vars *vars);
void			set_is_running(t_vars *vars, int value);
long long int	get_last_meal(t_philo *philo);
void			set_last_meal(t_philo *philo);
int				get_meals_ate(t_philo *philo);
void			set_meals_ate(t_philo *philo);
void			check_and_stop(t_philo *philos, int i, int *stop_flag);
void			unlock_forks(t_philo *philo);

#endif
