/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:43:37 by olidon            #+#    #+#             */
/*   Updated: 2021/01/20 15:38:08 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	ft_check_last_meal_time(t_last_meal *last_meal, struct timeval tv)
{
	if (((tv.tv_sec * 1000000 + tv.tv_usec - last_meal->time) >
		last_meal->death_time) || last_meal->ret[0] == 1)
	{
		pthread_mutex_unlock(&last_meal->last_meal_mutex[0]);
		if (last_meal->ret[0] != 1)
		{
			pthread_mutex_unlock(&last_meal->death_mutex[0]);
			if (ft_write_death(last_meal->i, last_meal))
				return (1);
		}
		else
			pthread_mutex_unlock(&last_meal->death_mutex[0]);
		return (1);
	}
	return (0);
}

void		*ft_check_death(void *data)
{
	t_last_meal		*last_meal;
	struct timeval	tv;

	last_meal = (t_last_meal *)data;
	pthread_mutex_lock(&last_meal->enough_eat_mutex[0]);
	while (last_meal->enough_eat != 1)
	{
		pthread_mutex_unlock(&last_meal->enough_eat_mutex[0]);
		usleep(1000);
		gettimeofday(&tv, NULL);
		pthread_mutex_lock(&last_meal->last_meal_mutex[0]);
		pthread_mutex_lock(&last_meal->death_mutex[0]);
		if (ft_check_last_meal_time(last_meal, tv))
			return (NULL);
		pthread_mutex_unlock(&last_meal->last_meal_mutex[0]);
		pthread_mutex_unlock(&last_meal->death_mutex[0]);
		pthread_mutex_lock(&last_meal->enough_eat_mutex[0]);
	}
	pthread_mutex_unlock(&last_meal->enough_eat_mutex[0]);
	return (NULL);
}
