/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death_thread.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:43:37 by olidon            #+#    #+#             */
/*   Updated: 2021/01/21 14:21:02 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		*ft_free_last_meal(t_phi *philo)
{
	if (pthread_join(philo->death_check, NULL))
		write(1, "Error on joining death check thread\n", 36);
	return (NULL);
}

static int	ft_check_last_meal_time(t_phi *philo, struct timeval tv)
{
	if (((tv.tv_sec * 1000000 + tv.tv_usec - philo->time) >
		philo->death_time))
	{
		sem_post(philo->last_meal_sem);
		ft_write_death(philo->i, philo);
		return (1);
	}
	return (0);
}

void		*ft_check_death(void *data)
{
	t_phi			*philo;
	struct timeval	tv;

	philo = (t_phi *)data;
	sem_wait(philo->enough_eat_sem);
	while (philo->enough_eat != 1)
	{
		sem_post(philo->enough_eat_sem);
		usleep(1000);
		gettimeofday(&tv, NULL);
		sem_wait(philo->last_meal_sem);
		if (ft_check_last_meal_time(philo, tv))
			return (NULL);
		sem_post(philo->last_meal_sem);
		sem_wait(philo->enough_eat_sem);
	}
	sem_post(philo->enough_eat_sem);
	sem_post(philo->ate_enough_sem);
	return (NULL);
}
