/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dasal <dasal@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:39:14 by dasal             #+#    #+#             */
/*   Updated: 2024/10/09 12:42:22 by dasal            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum	e_state
{
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}				t_state;

typedef struct	s_philo
{
	t_state	state;
	int		number;
}				t_philo;

#endif
