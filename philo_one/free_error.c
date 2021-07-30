/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:35:05 by olidon            #+#    #+#             */
/*   Updated: 2021/01/19 13:33:17 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*ft_error_last_meal_free(int error, int tofree,
									t_last_meal *last_meal, t_philo *philo)
{
	pthread_mutex_lock(&philo->death_mutex[0]);
	philo->ret[0] = 1;
	pthread_mutex_unlock(&philo->death_mutex[0]);
	pthread_mutex_lock(&philo->write_mutex[0]);
	if (error == 1)
		write(1, "Malloc error\n", 13);
	if (error == 2)
		write(1, "Mutex init failed\n", 18);
	if (error == 3)
		write(1, "Death check thread creation failed\n", 35);
	pthread_mutex_unlock(&philo->write_mutex[0]);
	if (tofree > 1)
		pthread_mutex_destroy(&last_meal->last_meal_mutex[0]);
	if (tofree > 2)
		pthread_mutex_destroy(&last_meal->enough_eat_mutex[0]);
	if (tofree > 0)
		free(last_meal);
	return (NULL);
}

int		ft_error_free(int error, int tofree, t_philo *philo)
{
	if (error == 1)
		write(1, "Malloc error\n", 13);
	if (error == 2)
		write(1, "Invalid arguments\n", 18);
	if (tofree > 0)
		free(philo->args);
	if (tofree > 1)
		free(philo->write_mutex);
	if (tofree > 2)
		free(philo->death_mutex);
	if (tofree > 3)
		free(philo->ret);
	if (tofree > 4)
		free(philo->philo_nbr);
	if (tofree > 5)
		free(philo->forks_mutex);
	return (0);
}

int		ft_destroy_mutexes(t_philo *philo, int error,
									int tofree, unsigned int size)
{
	unsigned int	i;

	if (error == 1)
		write(1, "Mutex init failed\n", 18);
	if (tofree > 0)
		pthread_mutex_destroy(&philo->write_mutex[0]);
	if (tofree > 1)
		pthread_mutex_destroy(&philo->death_mutex[0]);
	i = 0;
	if (tofree > 2)
	{
		while (i < size)
		{
			pthread_mutex_destroy(&philo->forks_mutex[i]);
			i++;
		}
	}
	return (0);
}

void	*ft_free_last_meal(t_last_meal *last_meal)
{
	if (pthread_join(last_meal->death_check, NULL))
		write(1, "Error on joining death check thread\n", 36);
	pthread_mutex_destroy(&last_meal->last_meal_mutex[0]);
	pthread_mutex_destroy(&last_meal->enough_eat_mutex[0]);
	free(last_meal);
	return (NULL);
}
