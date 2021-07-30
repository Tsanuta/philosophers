/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:43:37 by olidon            #+#    #+#             */
/*   Updated: 2021/01/20 17:06:41 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	ft_check_last_meal_time(t_last_meal *last_meal, struct timeval tv)
{
	if (((tv.tv_sec * 1000000 + tv.tv_usec - last_meal->time) >
		last_meal->death_time) || last_meal->ret[0] == 1)
	{
		sem_post(last_meal->last_meal_mutex);
		if (last_meal->ret[0] != 1)
		{
			sem_post(last_meal->death_mutex);
			if (ft_write_death(last_meal->i, last_meal))
				return (1);
		}
		else
			sem_post(last_meal->death_mutex);
		return (1);
	}
	return (0);
}

void		*ft_check_death(void *data)
{
	t_last_meal		*last_meal;
	struct timeval	tv;

	last_meal = (t_last_meal *)data;
	sem_wait(last_meal->enough_eat_mutex);
	while (last_meal->enough_eat != 1)
	{
		sem_post(last_meal->enough_eat_mutex);
		usleep(1000);
		gettimeofday(&tv, NULL);
		sem_wait(last_meal->last_meal_mutex);
		sem_wait(last_meal->death_mutex);
		if (ft_check_last_meal_time(last_meal, tv))
			return (NULL);
		sem_post(last_meal->last_meal_mutex);
		sem_post(last_meal->death_mutex);
		sem_wait(last_meal->enough_eat_mutex);
	}
	sem_post(last_meal->enough_eat_mutex);
	return (NULL);
}
