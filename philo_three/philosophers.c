/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:57:07 by olidon            #+#    #+#             */
/*   Updated: 2021/01/21 14:19:51 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	ft_only_one_fork(t_phi *philo)
{
	sem_wait(philo->forks_mutex);
	ft_write_action(philo->i, philo, 0);
	while (1)
	{
		if (ft_write_action(philo->i, philo, 5))
		{
			sem_post(philo->forks_mutex);
			ft_free_last_meal(philo);
			return (1);
		}
	}
}

static int	ft_take_forks(t_phi *philo)
{
	sem_wait(philo->forks_mutex);
	sem_wait(philo->forks_mutex);
	if (ft_write_action(philo->i, philo, 0)
		|| ft_write_action(philo->i, philo, 0))
	{
		sem_post(philo->forks_mutex);
		sem_post(philo->forks_mutex);
		ft_free_last_meal(philo);
		return (1);
	}
	return (0);
}

static int	ft_sleep(t_phi *philo, unsigned time_eating)
{
	if (philo->argc == 6 && time_eating == philo->nb_time_eating)
	{
		sem_wait(philo->enough_eat_sem);
		philo->enough_eat = 1;
		sem_post(philo->enough_eat_sem);
		ft_free_last_meal(philo);
		return (1);
	}
	else
	{
		if (ft_write_action(philo->i, philo, 2))
		{
			ft_free_last_meal(philo);
			return (1);
		}
		ft_sleep_time(philo->time_to_sleep * 1000);
		return (0);
	}
}

static int	ft_eat_and_sleep(t_phi *philo, unsigned time_eating)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	sem_wait(philo->last_meal_sem);
	philo->time = tv.tv_sec * 1000000 + tv.tv_usec;
	sem_post(philo->last_meal_sem);
	if (ft_write_action(philo->i, philo, 1))
	{
		sem_post(philo->forks_mutex);
		sem_post(philo->forks_mutex);
		ft_free_last_meal(philo);
		return (1);
	}
	ft_sleep_time(philo->time_to_eat * 1000);
	sem_post(philo->forks_mutex);
	ft_sleep_time(100);
	sem_post(philo->forks_mutex);
	if (ft_sleep(philo, time_eating))
		return (1);
	return (0);
}

void		philo_routine(t_phi *philo)
{
	unsigned int	time_eating;

	if (philo->argc == 6 && philo->nb_time_eating == 0)
	{
		sem_post(philo->ate_enough_sem);
		exit(EXIT_SUCCESS);
	}
	if (ft_create_last_meal(philo)
	|| (philo->j == 1 && ft_only_one_fork(philo)))
		exit(EXIT_SUCCESS);
	time_eating = 1;
	while (1)
	{
		if (ft_take_forks(philo))
			exit(EXIT_SUCCESS);
		if (ft_eat_and_sleep(philo, time_eating))
			exit(EXIT_SUCCESS);
		if (ft_write_action(philo->i, philo, 3))
		{
			ft_free_last_meal(philo);
			exit(EXIT_SUCCESS);
		}
		time_eating++;
	}
}
