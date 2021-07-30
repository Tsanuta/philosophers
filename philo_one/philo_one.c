/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:04:16 by olidon            #+#    #+#             */
/*   Updated: 2021/01/20 15:07:22 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		ft_philo_copy_struct(t_philo *philo, t_philo *phi, int i)
{
	phi->argc = philo->argc;
	phi->args = philo->args;
	phi->forks_mutex = philo->forks_mutex;
	phi->philo_nbr = philo->philo_nbr;
	phi->write_mutex = philo->write_mutex;
	phi->death_mutex = philo->death_mutex;
	phi->time = philo->time;
	phi->i = i + 1;
	phi->j = ft_is_last_fork(phi);
	phi->ret = philo->ret;
	phi->death_time = (long int)philo->args[1] * 1000;
	phi->nb_time_eating = philo->args[4];
	phi->time_to_sleep = philo->args[3];
	phi->time_to_eat = philo->args[2];
}

static int	ft_thread_join_error(t_philo *philo, unsigned int i)
{
	unsigned int	j;

	j = 0;
	pthread_mutex_lock(&philo->death_mutex[0]);
	philo->ret[0] = 1;
	pthread_mutex_unlock(&philo->death_mutex[0]);
	pthread_mutex_lock(&philo->write_mutex[0]);
	write(1, "Philosopher thread creation failed\n", 35);
	pthread_mutex_unlock(&philo->write_mutex[0]);
	while (j < i)
	{
		if (pthread_join(philo->philo_nbr[j], NULL))
		{
			pthread_mutex_lock(&philo->write_mutex[0]);
			write(1, "Error on joining philosopher thread\n", 36);
			pthread_mutex_unlock(&philo->write_mutex[0]);
			return (1);
		}
		j++;
	}
	return (1);
}

static int	ft_thread_start(t_philo *philo, t_philo *phi)
{
	unsigned int	i;

	i = 0;
	while (i < philo->args[0])
	{
		if (pthread_create(&philo->philo_nbr[i], NULL,
										philo_routine, (void *)&phi[i]))
			return (ft_thread_join_error(philo, i));
		ft_sleep_time(100);
		i++;
	}
	i = 0;
	while (i < philo->args[0])
	{
		if (pthread_join(philo->philo_nbr[i], NULL))
		{
			pthread_mutex_lock(&philo->write_mutex[0]);
			write(1, "Error on joining philosopher thread\n", 36);
			pthread_mutex_unlock(&philo->write_mutex[0]);
			return (1);
		}
		i++;
	}
	return (1);
}

int			ft_program_start(t_philo *philo)
{
	unsigned int	i;
	struct timeval	tv;
	t_philo			*phi;

	if (!(phi = malloc(sizeof(t_philo) * philo->args[0])))
		return (1);
	if (!(ft_mutexs_init(philo)))
	{
		free(phi);
		return (1);
	}
	gettimeofday(&tv, NULL);
	philo->time = tv.tv_sec * 1000000 + tv.tv_usec;
	i = 0;
	while (i < philo->args[0])
	{
		ft_philo_copy_struct(philo, &phi[i], i);
		i++;
	}
	if (ft_thread_start(philo, phi))
	{
		free(phi);
		return (0);
	}
	return (0);
}

int			main(int argc, char **argv)
{
	t_philo			philo;

	if (!(ft_init_struct(argc, argv, &philo)))
		return (0);
	if (!(ft_program_start(&philo)))
		ft_destroy_mutexes(&philo, 0, 3, philo.args[0]);
	ft_error_free(0, 6, &philo);
}
