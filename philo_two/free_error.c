/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:35:05 by olidon            #+#    #+#             */
/*   Updated: 2021/01/20 16:24:18 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	ft_write_error(int error, t_philo *philo)
{
	sem_wait(philo->write_mutex);
	if (error == 1)
		write(1, "Malloc error\n", 13);
	if (error == 2)
		write(1, "Semaphore open failed\n", 22);
	if (error == 3)
		write(1, "Death check thread creation failed\n", 35);
	sem_post(philo->write_mutex);
}

void		*ft_error_last_meal_free(int error,
							int tofree, t_last_meal *last_meal, t_philo *philo)
{
	sem_wait(philo->death_mutex);
	philo->ret[0] = 1;
	sem_post(philo->death_mutex);
	ft_write_error(error, philo);
	if (tofree > 3)
	{
		sem_close(last_meal->last_meal_mutex);
		sem_unlink(last_meal->last_meal_name);
	}
	if (tofree > 4)
	{
		sem_close(last_meal->enough_eat_mutex);
		sem_unlink(last_meal->enough_eat_name);
	}
	if (tofree > 1)
		free(last_meal->last_meal_name);
	if (tofree > 2)
		free(last_meal->enough_eat_name);
	if (tofree > 0)
		free(last_meal);
	return (NULL);
}

int			ft_error_free(int error, int tofree, t_philo *philo)
{
	if (error == 1)
		write(1, "Malloc error\n", 13);
	if (error == 2)
		write(1, "Invalid arguments\n", 18);
	if (tofree > 0)
		free(philo->args);
	if (tofree > 3)
		free(philo->ret);
	if (tofree > 4)
		free(philo->philo_nbr);
	return (0);
}

int			ft_destroy_mutexes(t_philo *philo, int error, int tofree)
{
	if (error == 1)
		write(1, "Semaphore open failed\n", 22);
	if (tofree > 0)
	{
		sem_close(philo->write_mutex);
		sem_unlink("/writesem");
	}
	if (tofree > 1)
	{
		sem_close(philo->death_mutex);
		sem_unlink("/deathsem");
	}
	if (tofree > 2)
	{
		sem_close(philo->forks_mutex);
		sem_unlink("/forkssem");
	}
	return (0);
}

void		*ft_free_last_meal(t_last_meal *last_meal)
{
	if (pthread_join(last_meal->death_check, NULL))
		write(1, "Error on joining death check thread\n", 36);
	sem_close(last_meal->last_meal_mutex);
	sem_unlink(last_meal->last_meal_name);
	sem_close(last_meal->enough_eat_mutex);
	sem_unlink(last_meal->enough_eat_name);
	free(last_meal->last_meal_name);
	free(last_meal->enough_eat_name);
	free(last_meal);
	return (NULL);
}
