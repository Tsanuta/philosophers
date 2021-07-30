/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:04:16 by olidon            #+#    #+#             */
/*   Updated: 2021/01/22 10:40:06 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	ft_free_child(t_philo *philo)
{
	unsigned int	j;

	free(philo->philo_nbr);
	free(philo->last_meal_sem);
	j = -1;
	while (++j < philo->args[0])
		free(philo->last_meal_name[j]);
	free(philo->last_meal_name);
	free(philo->enough_eat_sem);
	j = -1;
	while (++j < philo->args[0])
		free(philo->enough_eat_name[j]);
	free(philo->enough_eat_name);
	free(philo->ate_enough_sem);
	j = -1;
	while (++j < philo->args[0])
		free(philo->ate_enough_name[j]);
	free(philo->ate_enough_name);
	free(philo->args);
}

static void	ft_philo_copy_struct(t_philo *philo, t_phi *phi, int i)
{
	phi->argc = philo->argc;
	phi->forks_mutex = philo->forks_mutex;
	phi->write_mutex = philo->write_mutex;
	phi->is_dead_sem = philo->is_dead_sem;
	phi->i = i + 1;
	phi->j = philo->args[0];
	phi->time = philo->time;
	phi->init_time = philo->time;
	phi->nb_time_eating = philo->args[4];
	phi->death_time = (long int)philo->args[1] * 1000;
	phi->time_to_sleep = philo->args[3];
	phi->time_to_eat = philo->args[2];
	phi->last_meal_sem = philo->last_meal_sem[i];
	phi->enough_eat_sem = philo->enough_eat_sem[i];
	phi->ate_enough_sem = philo->ate_enough_sem[i];
	phi->enough_eat = 0;
}

static int	ft_thread_start(t_philo *philo, t_phi *phi)
{
	unsigned int	i;

	i = 0;
	while (i < philo->args[0])
	{
		phi->i = i + 1;
		phi->last_meal_sem = philo->last_meal_sem[i];
		phi->enough_eat_sem = philo->enough_eat_sem[i];
		phi->ate_enough_sem = philo->ate_enough_sem[i];
		if ((philo->philo_nbr[i] = fork()) < 0)
			return (ft_fork_error(philo, i));
		else if (philo->philo_nbr[i] == 0)
		{
			ft_free_child(philo);
			philo_routine(phi);
		}
		i++;
	}
	if (philo->args[0] == 0)
		return (1);
	if (!(ft_start_kill_threads(philo)))
		return (1);
	return (1);
}

int			ft_program_start(t_philo *philo)
{
	unsigned int	i;
	struct timeval	tv;
	t_phi			phi;

	if (!(ft_mutexs_init(philo)))
		return (1);
	gettimeofday(&tv, NULL);
	philo->time = tv.tv_sec * 1000000 + tv.tv_usec;
	i = 0;
	ft_philo_copy_struct(philo, &phi, i);
	if (ft_thread_start(philo, &phi))
		return (0);
	return (0);
}

int			main(int argc, char **argv)
{
	t_philo			philo;

	if (!(ft_init_struct(argc, argv, &philo)))
		return (0);
	if (!(ft_program_start(&philo)))
		ft_destroy_sem(&philo, 0, 9, 0);
	ft_error_free(0, 8, &philo);
}
