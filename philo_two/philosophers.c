/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 20:57:07 by olidon            #+#    #+#             */
/*   Updated: 2021/01/20 17:08:07 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static int	ft_only_one_fork(t_philo *philo, t_last_meal *last_meal)
{
	sem_wait(philo->forks_mutex);
	ft_write_action(philo->i, philo, 0);
	while (1)
	{
		if (ft_write_action(philo->i, philo, 5))
		{
			sem_post(philo->forks_mutex);
			ft_free_last_meal(last_meal);
			return (1);
		}
	}
}

static int	ft_take_forks(t_philo *philo, t_last_meal *last_meal)
{
	sem_wait(philo->forks_mutex);
	sem_wait(philo->forks_mutex);
	if (ft_write_action(philo->i, philo, 0)
		|| ft_write_action(philo->i, philo, 0))
	{
		sem_post(philo->forks_mutex);
		sem_post(philo->forks_mutex);
		ft_free_last_meal(last_meal);
		return (1);
	}
	return (0);
}

static int	ft_sleep(t_philo *philo,
							t_last_meal *last_meal, unsigned time_eating)
{
	if (philo->argc == 6 && time_eating == philo->nb_time_eating)
	{
		sem_wait(last_meal->enough_eat_mutex);
		last_meal->enough_eat = 1;
		sem_post(last_meal->enough_eat_mutex);
		ft_free_last_meal(last_meal);
		return (1);
	}
	else
	{
		if (ft_write_action(philo->i, philo, 2))
		{
			ft_free_last_meal(last_meal);
			return (1);
		}
		ft_sleep_time(philo->time_to_sleep * 1000);
		return (0);
	}
}

static int	ft_eat_and_sleep(t_philo *philo,
						t_last_meal *last_meal, unsigned time_eating)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	sem_wait(last_meal->last_meal_mutex);
	last_meal->time = tv.tv_sec * 1000000 + tv.tv_usec;
	sem_post(last_meal->last_meal_mutex);
	if (ft_write_action(philo->i, philo, 1))
	{
		sem_post(philo->forks_mutex);
		sem_post(philo->forks_mutex);
		ft_free_last_meal(last_meal);
		return (1);
	}
	ft_sleep_time(philo->time_to_eat * 1000);
	sem_post(philo->forks_mutex);
	ft_sleep_time(100);
	sem_post(philo->forks_mutex);
	if (ft_sleep(philo, last_meal, time_eating))
		return (1);
	return (0);
}

void		*philo_routine(void *data)
{
	t_philo			*philo;
	unsigned int	time_eating;
	t_last_meal		*last_meal;

	philo = (t_philo *)data;
	if (philo->argc == 6 && philo->nb_time_eating == 0)
		return (NULL);
	if (!(last_meal = ft_create_last_meal(philo)))
		return (NULL);
	time_eating = 1;
	if (philo->j == 1 && ft_only_one_fork(philo, last_meal))
		return (NULL);
	while (1)
	{
		if (ft_take_forks(philo, last_meal))
			return (NULL);
		if (ft_eat_and_sleep(philo, last_meal, time_eating))
			return (NULL);
		if (ft_write_action(philo->i, philo, 3))
			return (ft_free_last_meal(last_meal));
		time_eating++;
	}
}
