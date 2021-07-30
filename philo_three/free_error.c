/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:35:05 by olidon            #+#    #+#             */
/*   Updated: 2021/01/21 12:46:55 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			ft_error_free(int error, int tofree, t_philo *philo)
{
	if (error == 1)
		write(1, "Malloc error\n", 13);
	if (error == 2)
		write(1, "Invalid arguments\n", 18);
	if (tofree > 0)
		free(philo->args);
	if (tofree > 1)
		free(philo->philo_nbr);
	if (tofree > 2)
		free(philo->last_meal_sem);
	if (tofree > 3)
		free(philo->last_meal_name);
	if (tofree > 4)
		free(philo->enough_eat_sem);
	if (tofree > 5)
		free(philo->enough_eat_name);
	if (tofree > 6)
		free(philo->ate_enough_sem);
	if (tofree > 7)
		free(philo->ate_enough_name);
	return (0);
}

static void	ft_del_last_meal(t_philo *philo, int tofree, int index)
{
	int		j;
	int		i;

	j = philo->args[0];
	if (tofree == 4)
		j = index;
	if (tofree >= 4)
	{
		i = -1;
		while (++i < j)
		{
			sem_close(philo->last_meal_sem[i]);
			sem_unlink(philo->last_meal_name[i]);
		}
	}
	if (tofree == 3)
		j = index;
	if (tofree >= 3)
	{
		i = -1;
		while (++i < j)
			free(philo->last_meal_name[i]);
	}
}

static void	ft_del_enough_eat(t_philo *philo, int tofree, int index)
{
	int		j;
	int		i;

	j = philo->args[0];
	if (tofree == 6)
		j = index;
	if (tofree >= 6)
	{
		i = -1;
		while (++i < j)
		{
			sem_close(philo->enough_eat_sem[i]);
			sem_unlink(philo->enough_eat_name[i]);
		}
	}
	if (tofree == 5)
		j = index;
	if (tofree >= 5)
	{
		i = -1;
		while (++i < j)
			free(philo->enough_eat_name[i]);
	}
}

static void	ft_del_ate_enough(t_philo *philo, int tofree, int index)
{
	int		j;
	int		i;

	j = philo->args[0];
	if (tofree == 8)
		j = index;
	if (tofree >= 8)
	{
		i = -1;
		while (++i < j)
		{
			sem_close(philo->ate_enough_sem[i]);
			sem_unlink(philo->ate_enough_name[i]);
		}
	}
	if (tofree == 7)
		j = index;
	if (tofree >= 7)
	{
		i = -1;
		while (++i < j)
			free(philo->ate_enough_name[i]);
	}
}

int			ft_destroy_sem(t_philo *philo, int error, int tofree, int index)
{
	if (error == 1)
		write(1, "Semaphore open failed\n", 22);
	if (error == 2)
		write(1, "Malloc error\n", 13);
	if (tofree > 0)
	{
		sem_close(philo->write_mutex);
		sem_unlink("/writesem");
	}
	if (tofree > 1)
	{
		sem_close(philo->is_dead_sem);
		sem_unlink("/isdeadsem");
	}
	if (tofree > 2)
	{
		sem_close(philo->forks_mutex);
		sem_unlink("/forkssem");
	}
	ft_del_last_meal(philo, tofree, index);
	ft_del_enough_eat(philo, tofree, index);
	ft_del_ate_enough(philo, tofree, index);
	return (0);
}
