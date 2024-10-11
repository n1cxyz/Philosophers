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

int	ft_atoi(const char *str)
{
	int	nbr;
	int	sign;

	sign = 1;
	nbr = 0;
	while (is_space((char) *str) != 0)
		str++;
	if (ft_strncmp(str, "-2147483648", 11) == 0)
		return (-2147483648);
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str) != 0)
	{
		nbr = nbr * 10;
		nbr = nbr + *str - 48;
		str++;
	}
	return (sign * nbr);
}

int	ft_is_space(int c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
	{
		return (8192);
	}
	return (0);
}

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (2048);
	}
	return (0);
}