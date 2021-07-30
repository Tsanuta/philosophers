/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_kill_threads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:42:01 by olidon            #+#    #+#             */
/*   Updated: 2021/01/21 14:21:57 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	*ft_kill_enough(void *data)
{
	t_philo			*philo;
	unsigned int	i;

	i = 0;
	philo = (t_philo *)data;
	if (philo->argc == 6)
	{
		while (i < philo->args[0])
		{
			sem_wait(philo->ate_enough_sem[i]);
			i++;
		}
	}
	else
		return (NULL);
	sem_post(philo->is_dead_sem);
	return (NULL);
}

static void	*ft_kill_process(void *data)
{
	t_philo			*philo;
	unsigned int	i;

	philo = (t_philo *)data;
	sem_wait(philo->is_dead_sem);
	i = 0;
	while (i < philo->args[0])
	{
		sem_post(philo->ate_enough_sem[i]);
		kill(philo->philo_nbr[i], SIGKILL);
		i++;
	}
	return (NULL);
}

int			ft_start_kill_threads(t_philo *philo)
{
	pthread_t		kill_process;
	pthread_t		kill_enough;

	if (pthread_create(&kill_process, NULL, ft_kill_process, (void *)philo))
	{
		write(1, "Kill process thread creation failed\n", 36);
		return (1);
	}
	if (pthread_create(&kill_enough, NULL, ft_kill_enough, (void *)philo))
	{
		write(1, "Kill process thread creation failed\n", 36);
		return (1);
	}
	if (pthread_detach(kill_enough))
		write(1, "Error on joining kill process thread\n", 37);
	if (pthread_join(kill_process, NULL))
		write(1, "Error on joining kill process thread\n", 37);
	return (1);
}
