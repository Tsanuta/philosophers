/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:25:11 by olidon            #+#    #+#             */
/*   Updated: 2021/01/18 15:58:11 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static int	ft_last_meal_sem_init(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < philo->args[0])
	{
		if (!(philo->last_meal_name[i] =
								ft_strjoin("/lastmeal", ft_itoa(i))))
			return (ft_destroy_sem(philo, 2, 3, i));
		i++;
	}
	i = 0;
	while (i < philo->args[0])
	{
		sem_unlink(philo->last_meal_name[i]);
		if (SEM_FAILED == (philo->last_meal_sem[i] =
			sem_open(philo->last_meal_name[i], O_CREAT, S_IRWXU, 1)))
			return (ft_destroy_sem(philo, 1, 4, i));
		i++;
	}
	return (1);
}

static int	ft_enough_eat_sem_init(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < philo->args[0])
	{
		if (!(philo->enough_eat_name[i] =
								ft_strjoin("/enougheat", ft_itoa(i))))
			return (ft_destroy_sem(philo, 2, 5, i));
		i++;
	}
	i = 0;
	while (i < philo->args[0])
	{
		sem_unlink(philo->enough_eat_name[i]);
		if (SEM_FAILED == (philo->enough_eat_sem[i] =
			sem_open(philo->enough_eat_name[i], O_CREAT, S_IRWXU, 1)))
			return (ft_destroy_sem(philo, 1, 6, i));
		i++;
	}
	return (1);
}

static int	ft_ate_enough_sem_init(t_philo *philo)
{
	unsigned int	i;

	i = 0;
	while (i < philo->args[0])
	{
		if (!(philo->ate_enough_name[i] =
								ft_strjoin("/ateenough", ft_itoa(i))))
			return (ft_destroy_sem(philo, 2, 7, i));
		i++;
	}
	i = 0;
	while (i < philo->args[0])
	{
		sem_unlink(philo->ate_enough_name[i]);
		if (SEM_FAILED == (philo->ate_enough_sem[i] =
			sem_open(philo->ate_enough_name[i], O_CREAT, S_IRWXU, 0)))
			return (ft_destroy_sem(philo, 1, 8, i));
		i++;
	}
	return (1);
}

int			ft_mutexs_init(t_philo *philo)
{
	sem_unlink("/writesem");
	if (SEM_FAILED ==
		(philo->write_mutex = sem_open("/writesem", O_CREAT, S_IRWXU, 1)))
		return (ft_destroy_sem(philo, 1, 0, 0));
	sem_unlink("/isdeadsem");
	if (SEM_FAILED ==
		(philo->is_dead_sem = sem_open("/isdeadsem", O_CREAT, S_IRWXU, 0)))
		return (ft_destroy_sem(philo, 1, 1, 0));
	sem_unlink("/forkssem");
	if (SEM_FAILED == (philo->forks_mutex =
				sem_open("/forkssem", O_CREAT, S_IRWXU, philo->args[0])))
		return (ft_destroy_sem(philo, 1, 2, 0));
	if (!(ft_last_meal_sem_init(philo)))
		return (0);
	if (!(ft_enough_eat_sem_init(philo)))
		return (0);
	if (!(ft_ate_enough_sem_init(philo)))
		return (0);
	return (1);
}
