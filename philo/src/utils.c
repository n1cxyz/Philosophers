/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:48:41 by dasal             #+#    #+#             */
/*   Updated: 2024/10/11 11:48:42 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	atoi(const char *str)
{
	size_t			i;
	long long int	result;

	i = 0;
	result = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
		return (-1);
	while (str[i] == '+')
		i++;
	while (is_digit(str[i]))
	{
		result *= 10;
		result += str[i] - '0';
		if (result > 2147483647)
			return (-1);
		i++;
	}
	if (str[i] != '\0')
		return (-1);
	return (result);
}

int	is_space(int c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
	{
		return (8192);
	}
	return (0);
}

int	is_digit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (2048);
	}
	return (0);
}

unsigned int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	ft_sleep(t_vars *vars, long long time)
{
	long long current_time;

	current_time = get_time();
	while (vars->is_running)
	{
		if (get_time() - current_time >= time)
			break ;
		usleep(500);
	}
}